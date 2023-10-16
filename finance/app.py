import os

from cs50 import SQL
from datetime import datetime
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    index = db.execute(
        "SELECT symbol, SUM(shares) FROM transactions WHERE user_id = ? GROUP BY symbol",
        session["user_id"],
    )

    prices = {}
    totals = {}
    balance = 0

    for stock in index:
        symbol = stock["symbol"]
        price = lookup(stock["symbol"])
        total = stock["SUM(shares)"] * price["price"]

        prices[symbol] = usd(price["price"])
        totals[symbol] = usd(total)

        balance += total

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

    balance += cash[0]["cash"]

    return render_template(
        "index.html",
        index=index,
        prices=prices,
        totals=totals,
        cash=usd(cash[0]["cash"]),
        balance=usd(balance),
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)
        symbol = request.form.get("symbol")

        if lookup(symbol) == None:
            return apology("stock symbol not found", 400)

        if not request.form.get("shares"):
            return apology("must provide number of shares", 400)
        shares = request.form.get("shares")

        if not shares.isnumeric():
            return apology("quantity must be a number", 400)

        if float(shares) % 1 != 0:
            return apology("quantity must be a whole number", 400)

        if float(shares) <= 0:
            return apology("invalid number of shares", 400)

        shares = float(shares)

        quote = lookup(symbol)
        cost = quote["price"] * int(shares)

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        balance = cash[0]["cash"] - cost

        if cost > cash[0]["cash"]:
            return apology("purchase exceeds balance", 403)
        else:
            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"]
            )
            db.execute(
                "INSERT INTO transactions (user_id, symbol, shares, price, transacted) VALUES (?, ?, ?, ?, ?)",
                session["user_id"],
                symbol,
                int(shares),
                quote["price"],
                datetime.now(),
            )
            return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT symbol, shares, price, transacted FROM transactions WHERE user_id = ?",
        session["user_id"],
    )

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("invalid ticker symbol", 400)

        symbol = request.form.get("symbol")

        if lookup(symbol) == None:
            return apology("ticker symbol not found", 400)

        quote = lookup(symbol)

        return render_template("quoted.html", price=usd(quote["price"]))

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)

        # Ensure passwords match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 0:
            return apology("username exists", 400)

        db.execute(
            "INSERT INTO users (username, hash) VALUES(?, ?)",
            request.form.get("username"),
            generate_password_hash(request.form.get("password")),
        )
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quantity = request.form.get("shares")

        index = db.execute(
            "SELECT SUM(shares) FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol",
            session["user_id"],
            symbol,
        )

        shares = index[0]["SUM(shares)"]
        quote = lookup(symbol)

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        balance = cash[0]["cash"] + quote["price"] * int(quantity)

        if int(quantity) > shares:
            return apology("not enough shares")

        if int(quantity) <= 0:
            return apology("invalid quantity")

        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, transacted) VALUES (?, ?, ?, ?, ?)",
            session["user_id"],
            symbol,
            int(quantity) * (-1),
            quote["price"],
            datetime.now(),
        )
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"]
        )
        return redirect("/")

    else:
        index = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol",
            session["user_id"],
        )

        return render_template("sell.html", index=index)


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    if request.method == "POST":
        amount = request.form.get("deposit")

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        balance = round(cash[0]["cash"] + float(amount), 2)

        print(balance)

        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"]
        )

        return redirect("/")
    else:
        return render_template("deposit.html")
