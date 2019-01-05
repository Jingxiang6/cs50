import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get the user_id
    user_id = session["user_id"]

    # Initialize stock_value to store total stock value
    stock_value = 0

    # Extract symbol and shares information from table actions, and sum the shares of the same stock
    symbol_shares = db.execute("SELECT symbol, SUM(shares) AS shares FROM actions WHERE user_id = :id GROUP BY symbol", id=user_id)

    # Get the stock's current price by using the lookup function in heplers.py, and calculate the total vaule of each stock
    # and the total value of stocks
    for i in range(len(symbol_shares)):
        symbol_shares[i]["price"] = lookup(symbol_shares[i]["symbol"])["price"]
        symbol_shares[i]["total_value"] = symbol_shares[i]["price"] * symbol_shares[i]["shares"]
        stock_value += symbol_shares[i]["total_value"]

    # Select cash value of the user
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)[0]["cash"]
    # Grand total value (cash + stock)
    total = cash + stock_value
    # Display the index.html page
    return render_template("index.html", symbol_shares=symbol_shares, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Get the user_id
    user_id = session["user_id"]

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure stock symbol was submitted
        if not symbol:
            return apology("Must provide symbol", 400)

        # Check the stock symbol using function lookup in helpers.py
        quote = lookup(symbol)

        # Ensure the stock symbol is valid
        if not quote:
            return apology("Symbol is invalid", 400)

        # Ensure shares was submitted
        if not shares:
            return apology("Must provide shares", 400)

        try:
            shares = int(shares)
        except ValueError as cause:
            return apology("Shares must be an integer", 400)
        if not shares > 0:
            return apology("Shares must be a positive integer", 400)

        # Check the stock price using function lookup in helpers.py, and calculate cost to buy stock
        price = lookup(symbol)["price"]
        cost = price * int(shares)

        # Select cash value of the user
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)[0]["cash"]

        # Check is cash enough to buy shares of stock
        if cost > cash:
            return apology("Can't afford to buy {} shares of {}".format(shares, symbol), 403)

        else:
            # Insert buy information to table actions
            db.execute("INSERT INTO actions (user_id, symbol, price, time, shares, act) VALUES \
                       (:user_id, :symbol, :price, :time, :shares, :act)",
                       user_id=user_id,
                       symbol=lookup(symbol)["symbol"],
                       price=price,
                       time=datetime.now(),
                       shares=shares,
                       act="buy")

            # Update cash in table users
            db.execute("UPDATE users SET cash = ROUND(cash - :cost,2) WHERE id = :id", cost=cost, id=user_id)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Get the user_id
    user_id = session["user_id"]

    # Extract all the actions done by the user
    hist = db.execute("SELECT * FROM actions WHERE user_id = :id", id=user_id)

    # Direct the user to history.html page
    return render_template("history.html", hist=hist)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    # User reached route via POST (as by submitting a form via POST)
    # User reached route via GET (as by clicking a link or via redirect)
    if request.method != "POST":
        return render_template("quote.html")

    # Ensure a stock symbol was submitted
    if not request.form.get("symbol"):
        return apology("Must provide symbol", 400)

    # Check the stock symbol using function lookup in helpers.py
    quote = lookup(request.form.get("symbol"))

    # Ensure the stock symbol is valid
    if not quote:
        return apology("Symbol is invalid", 400)

    # Redirect user to quoted.html page
    return render_template("quoted.html", name=quote["name"], price=quote["price"], symbol=quote["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("Missing username!", 400)

        # Check the username not exist in database
        result = db.execute("SELECT id FROM users WHERE username = :username",
                            username=request.form.get("username"))
        if result:
            return apology("Username is already exist!", 400)

        # Get the password
        password = request.form.get("password")

        # Ensure password was submitted
        if not password:
            return apology("Missing password!", 400)

        # password length >= 8
        if len(password) < 8:
            return apology("Password is too short", 400)

        # password contain at least one letter, one number
        test1 = 0
        test2 = 0
        for character in password:
            if character.isalpha():
                test1 = 1
            elif character.isnumeric():
                test2 = 1
        if test1 == 0:
            return apology("Password must contain at least one letter", 400)
        if test2 == 0:
            return apology("Password must contain at least one number", 400)

        # Ensure the password confirmation matches password
        elif not password == request.form.get("confirmation"):
            return apology("Password doesn't match!", 400)

        else:
            # Generate password hash
            pwhash = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)

            # Insert the username and hash into database
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                       username=request.form.get("username"),
                       hash=pwhash)

            # Query database for username
            rows = db.execute("SELECT * FROM users WHERE username = :username",
                              username=request.form.get("username"))
            # Remember which user has logged in
            session["user_id"] = rows[0]["id"]

            # Redirect user to home page
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Get the user_id
    user_id = session["user_id"]

    # Get all stock symbols from actions table
    symbols = db.execute("SELECT DISTINCT symbol FROM actions ORDER BY symbol")

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure stock was selected
        symbol = request.form.get('symbol')
        if not symbol:
            return apology("Must select a symbol", 403)

        # Get the stock and shares if the user owns any
        row = db.execute(
            "SELECT symbol, SUM(shares) AS shares FROM actions WHERE user_id = :id AND symbol = :symbol",
            id=user_id, symbol=symbol)
        # Ensure the selected stock symbol is owned by user
        if not row:
            return apology("You don't own the stock", 403)

        # Ensure shares was submitted
        shares = request.form.get("shares")
        if not shares:
            return apology("Must provide shares", 400)

        # Ensure shares > 0 integer
        elif int(shares) <= 0:
            return apology("shares must be a positive integer", 400)

        elif int(shares) > row[0]["shares"]:
            return apology("You own {} shares {}".format(row[0]["shares"], symbol), 400)

        # Check the stock price using function lookup in helpers.py, and calculate earns to sell stocks
        price = lookup(symbol)["price"]
        earn = price * int(shares)

        # Select cash value of the user
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)[0]["cash"]

        # Insert sell information to table actions
        db.execute("INSERT INTO actions (user_id, symbol, price, time, shares, act) VALUES \
                   (:user_id, :symbol, :price, :time, :shares, :act)",
                   user_id=user_id,
                   symbol=lookup(symbol)["symbol"],
                   price=price,
                   time=datetime.now(),
                   shares=(-1) * int(shares),
                   act="sell")

        # Update cash in table users
        db.execute("UPDATE users SET cash = cash + :earn WHERE id = :id", earn=earn, id=user_id, )

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
