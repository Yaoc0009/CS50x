import csv

from cs50 import SQL

# Create empty db file
open("shows.db", "w").close()
# Connect to database
db = SQL("sqlite:///shows.db")

# Create empty shows table
db.execute("CREATE TABLE shows (id INTEGER, title TEXT, PRIMARY KEY(id))")
# Create empty genres table
db.execute("CREATE TABLE genres (show_id INTEGER, genre TEXT, FOREIGN KEY(show_id) REFERENCES shows(id))")

# Open csv file
with open("Favorite TV Shows - Form Responses 1.csv", "r") as file:
    reader = csv.Dictreader(file)
    for row in reader:
        # Remove whitespaces, capitalize char
        title = row["title"].strip().upper()

        # Insert into shows table
        id = db.execute("INSERT INTO shows (title) VALUES(?)", title)

        for genre in row["genres"].split(", "):
            # Insert into genres table
            db.execute("INSERT INTO genres (show_id, genre) VALUES(?, ?)", id, genre)
