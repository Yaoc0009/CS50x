-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Who the thief is,
-- What city the thief escaped to, and
-- Who the thief’s accomplice is who helped them escape
-- All you know is that the theft took place on July 28, 2020 and that it took place on Chamberlin Street.

-- 1) Find related crime scene reports
SELECT description FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28
    AND street = "Chamberlin Street";
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

-- 2) Find witnesses and transcripts from interviews table
SELECT name, transcript FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28
    AND transcript LIKE "%courthouse%";
-- name | transcript
-- Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- 3) Check security logs around 10.15am, entrance before, exit 10mins after - find license plate, find people corresponding to the license plates
SELECT name FROM people
WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs
WHERE (year = 2020 AND month = 7 AND day = 28)
    AND (activity = 'exit')
    AND (TIME(SUBSTR('00' || hour, -2) || ':' || SUBSTR('00' || minute, -2)) > '10:15:00')
    AND (TIME(SUBSTR('00' || hour, -2) || ':' || SUBSTR('00' || minute, -2)) < '10:25:00'));
-- name
-- Patrick
-- Amber
-- Elizabeth
-- Roger
-- Danielle
-- Russell
-- Evelyn
-- Ernest

-- 4) ATM on Fifer street
-- Find bank account associated
-- Find name of person associated
SELECT p.name FROM people p
INNER JOIN bank_accounts b ON b.person_id = p.id
INNER JOIN atm_transactions a ON a.account_number = b.account_number
WHERE (a.year = 2020 AND a.month = 7 AND a.day = 28)
    AND (a.atm_location = 'Fifer Street')
    AND (a.transaction_type = 'withdraw');
-- name
-- Ernest
-- Russell
-- Roy
-- Bobby
-- Elizabeth
-- Danielle
-- Madison
-- Victoria

-- 5) Find earliest flight out of fiftyville the next day - retrieve passengers on the flight
SELECT p.name FROM people p
INNER JOIN passengers pass ON pass.passport_number = p.passport_number
WHERE pass.flight_id IN
(SELECT f.id FROM flights f
INNER JOIN airports a ON f.origin_airport_id = a.id
WHERE (f.year = 2020 AND f.month = 7 AND f.day = 29)
    AND a.city = 'Fiftyville'
ORDER BY f.hour, f.minute LIMIT 1);
-- name
-- Nicole
-- Amanda
-- Joyce
-- Jean
-- Daniel
-- Carol
-- Rebecca
-- Sophia

-- 6) Check phone call, less than a minute, while leaving the courthouse
SELECT caller.name AS caller, receiver.name AS receiver FROM (
(SELECT ROW_NUMBER () OVER (ORDER BY pc.id) AS row, p.name FROM people p
INNER JOIN phone_calls pc ON pc.caller = p.phone_number
WHERE (pc.year = 2020 AND pc.month = 7 AND pc.day = 28)
    AND pc.duration < 60
) AS caller
INNER JOIN
(SELECT ROW_NUMBER () OVER (ORDER BY pc.id) AS row, p.name FROM people p
INNER JOIN phone_calls pc ON pc.receiver = p.phone_number
WHERE (pc.year = 2020 AND pc.month = 7 AND pc.day = 28)
    AND pc.duration < 60
) AS receiver
ON caller.row = receiver.row);
-- caller | receiver
-- Roger | Jack
-- Evelyn | Larry
-- Ernest | Berthold
-- Evelyn | Melissa
-- Madison | James
-- Russell | Philip
-- Kimberly | Jacqueline
-- Bobby | Doris
-- Victoria | Anna

-- 7) Intersect information available to find thief
SELECT name FROM people
WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs
WHERE (year = 2020 AND month = 7 AND day = 28)
    AND (activity = 'exit')
    AND (TIME(SUBSTR('00' || hour, -2) || ':' || SUBSTR('00' || minute, -2)) > '10:15:00')
    AND (TIME(SUBSTR('00' || hour, -2) || ':' || SUBSTR('00' || minute, -2)) < '10:25:00'))

INTERSECT

SELECT p.name FROM people p
INNER JOIN bank_accounts b ON b.person_id = p.id
INNER JOIN atm_transactions a ON a.account_number = b.account_number
WHERE (a.year = 2020 AND a.month = 7 AND a.day = 28)
    AND (a.atm_location = 'Fifer Street')
    AND (a.transaction_type = 'withdraw')

INTERSECT

SELECT p.name FROM people p
INNER JOIN passengers pass ON pass.passport_number = p.passport_number
WHERE pass.flight_id IN
(SELECT f.id FROM flights f
INNER JOIN airports a ON f.origin_airport_id = a.id
WHERE (f.year = 2020 AND f.month = 7 AND f.day = 29)
    AND a.city = 'Fiftyville'
ORDER BY f.hour, f.minute LIMIT 1)

INTERSECT

SELECT p.name FROM people p
INNER JOIN phone_calls pc ON pc.caller = p.phone_number
WHERE (pc.year = 2020 AND pc.month = 7 AND pc.day = 28)
    AND pc.duration < 60;
-- name
-- Ernest

-- 8) Find accomplice with the call log
SELECT caller.name AS caller, receiver.name AS receiver FROM (
(SELECT ROW_NUMBER () OVER (ORDER BY pc.id) AS row, p.name FROM people p
INNER JOIN phone_calls pc ON pc.caller = p.phone_number
WHERE (pc.year = 2020 AND pc.month = 7 AND pc.day = 28)
    AND pc.duration < 60
) AS caller
INNER JOIN
(SELECT ROW_NUMBER () OVER (ORDER BY pc.id) AS row, p.name FROM people p
INNER JOIN phone_calls pc ON pc.receiver = p.phone_number
WHERE (pc.year = 2020 AND pc.month = 7 AND pc.day = 28)
    AND pc.duration < 60
) AS receiver
ON caller.row = receiver.row)
WHERE caller = 'Ernest';
-- caller | receiver
-- Ernest | Berthold

-- 9) Find city which the thief escaped to
SELECT a.city FROM airports a
WHERE id IN
(SELECT f.destination_airport_id FROM flights f
INNER JOIN airports a ON f.origin_airport_id = a.id
WHERE (f.year = 2020 AND f.month = 7 AND f.day = 29)
    AND a.city = 'Fiftyville'
ORDER BY f.hour, f.minute LIMIT 1);
-- city
-- London