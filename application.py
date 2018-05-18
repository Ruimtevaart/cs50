import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Ensure environment variable is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

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
    index1 = db.execute("SELECT * FROM stocks WHERE id = :session", session=session["user_id"])
    totalsum = db.execute("SELECT SUM(total) as suma FROM stocks WHERE id = :session", session=session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = :session", session=session["user_id"])
    return render_template("index.html", index1=index1, totalsum=usd(totalsum[0]["suma"] + cash[0]["cash"]), cash=usd(cash[0]["cash"]))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        user = db.execute("SELECT id FROM users WHERE id = :session",
                          session=session["user_id"])
        cash = db.execute("SELECT cash FROM users WHERE id = :session",
                          session=session["user_id"])
        buy = lookup(symbol)
        if (buy is None):
            return apology("Invalid symbol")
        elif (cash[0]["cash"] < (buy["price"] * shares)):
            return apology("Invalid amount of CASH")
        else:
            db.execute("UPDATE users SET cash = :cash WHERE id = :user",
                       user=user[0]["id"], cash=(cash[0]["cash"] - (buy["price"] * shares)))
            db.execute("INSERT INTO history (User, Symbol, Shares, Price) VALUES (:User, :Symbol, :Shares, :Price)",
                       User=user[0]["id"], Symbol=symbol, Shares=shares, Price=buy["price"])
            findstock = db.execute("SELECT shares FROM stocks WHERE id = :user AND symbol = :symbol",
                                   user=user[0]["id"], symbol=symbol)
            findprice = db.execute("SELECT total FROM stocks WHERE id = :user AND symbol = :symbol",
                                   user=user[0]["id"], symbol=symbol)
            if not findstock:
                db.execute("INSERT INTO stocks (id, symbol, shares, price, total) VALUES (:user, :symbol, :shares, :price, :total)",
                           user=user[0]["id"], symbol=symbol, shares=shares, price=buy["price"], total=shares * buy["price"])
            else:
                totalshares = findstock[0]["shares"] + shares
                totalprice = int(findprice[0]["total"]) + shares * buy["price"]
                db.execute("UPDATE stocks SET shares = :shares, total = :total WHERE id = :user AND symbol = :symbol",
                           shares=totalshares, total=totalprice, user=user[0]["id"], symbol=symbol)
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history1 = db.execute("SELECT * FROM History WHERE User = :session", session=session["user_id"])
    return render_template("history.html", history1=history1)


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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if (quote is None):
            return apology("Invalid symbol")
        else:
            return render_template("quoted.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username:
            return apology("must provide username", 400)
        elif not password:
            return apology("must provide password", 400)
        elif not confirmation:
            return apology("must provide confirmation", 400)
        if (password != confirmation):
            return apology("Missmatching passwords!")
        userfind = db.execute("SELECT id FROM users WHERE username = :username",
                              username=username)
        if userfind:
            return apology("Username already exists!", 400)
        passhash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :passhash)",
                   username=username, passhash=passhash)
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=username)
        session["user_id"] = rows[0]["id"]
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        user = db.execute("SELECT id FROM users WHERE id = :session", session=session["user_id"])
        cash = db.execute("SELECT cash FROM users WHERE id = :session", session=session["user_id"])
        sell = lookup(symbol)
        currentshares = db.execute("SELECT shares FROM stocks WHERE id = :session AND symbol = :symbol",
                                   session=session["user_id"], symbol=symbol)
        if int(currentshares[0]["shares"]) < shares:
            return apology("Too little shares left")
        if (sell is None):
            return apology("Invalid symbol")
        else:
            db.execute("UPDATE users SET cash = :cash WHERE id = :user",
                       user=user[0]["id"], cash=(cash[0]["cash"] + (sell["price"] * shares)))
            db.execute("INSERT INTO history (User, Symbol, Shares, Price) VALUES (:User, :Symbol, :Shares, :Price)",
                       User=user[0]["id"], Symbol=symbol, Shares=shares, Price=(-(sell["price"])))
            finalshares = int(currentshares[0]["shares"]) - shares
            if finalshares == 0:
                db.execute("DELETE FROM stocks WHERE id=:session AND symbol = :symbol", session=session["user_id"], symbol=symbol)
            else:
                totalprice = finalshares * sell["price"]
                db.execute("UPDATE stocks SET shares = :shares, total = :total WHERE id = :session AND symbol = :symbol",
                           shares=finalshares, total=totalprice, session=session["user_id"], symbol=symbol)
            return redirect("/")
    else:
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
