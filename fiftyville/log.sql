-- Keep a log of any SQL queries you execute as you solve the mystery.

-- crime scene report
-- SELECT id, description FROM crime_scene_reports
-- WHERE year = 2021
-- AND month = 7
-- AND day = 28
-- AND street = 'Humphrey Street'
-- AND description LIKE '%duck%';
--
-- report id = 295: Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each
-- of their interview transcripts mentions the bakery.

-- interviews that mention 'bakery'
-- SELECT id, name, transcript FROM interviews
-- WHERE transcript LIKE '%bakery%';
-- Ruth, Raymond, and Kiana saw the thief at the bakery
-- Eugene saw the thief withdrawing money from an ATM on Leggett Street some time in the morning

-- bakery transactions and security logs 10am - 10:15
-- SELECT id, hour, minute, activity, license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10;
-- license plates that exited bakery ~10:15am: 5P2BI95, 94KL13X, 6P58WS2
-- name (id): Vanessa (221103), Barry (243696), Bruce (686048)

-- atm transactions
-- SELECT * FROM atm_transactions  JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number JOIN people ON bank_accounts.person_id = people.id
-- WHERE atm_location LIKE '%Leggett%' AND month = 7 AND day = 28;
-- names: Bruce (5773159633), Kaelyn, Diana, Brooke, Kenny, Iman, Luca, Taylor, BEnista

-- flights from fiftyville for Bruce
SELECT flight_id, name, city FROM flights
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON passengers.passport_number = people.passport_number
JOIN airports ON flights.destination_airport_id = airports.id
WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
AND year = 2021
AND month = 7
AND day = 29
AND name = 'Bruce'
ORDER BY hour;

-- phone calls from Bruce
SELECT * FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE year = 2021
AND month = 7
AND day = 28
AND people.name = 'Bruce';