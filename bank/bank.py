greeting = input("Greeting: ")
greeting = greeting.lower()
greeting = greeting.lstrip()

if "hello" in greeting[0:5]:
    print("$0")
elif "h" in greeting[0]:
    print("$20")
else:
    print("$100")