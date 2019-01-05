import os
import re
from flask import Flask, jsonify, render_template, request

from cs50 import SQL
from helpers import lookup

# Configure application
app = Flask(__name__)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///mashup.db")


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
def index():
    """Render map"""
    return render_template("index.html")


@app.route("/articles")
def articles():
    """Look up articles for geo"""

    # Ensure parameters are present
    if not request.args.get("geo"):
        raise RuntimeError("missing geo")
    # Get articles using lookup function in helper.py
    article = lookup(request.args.get("geo"))
    # Pick the top 5 acticles
    result = article[:5]
    # Output places as JSON
    return jsonify(result)


@app.route("/search")
def search():
    """Search for places that match query"""

    # Get the string the user typed in
    q = request.args.get("q")
    # Remove ;,+(space) from the string q
    item = re.split(';|,|\+| ', q)
    item = [x for x in item if x != '']
    # Search items from table place applying AND and OR with WHERE LIKE in sqlite
    sql_statement = "SELECT * FROM places WHERE"
    for i in range(len(item)):
        quote = "'%" + item[i] + "%'"
        condition = " (country_code LIKE {quote}\
                    OR postal_code LIKE {quote}\
                    OR place_name LIKE {quote}\
                    OR admin_name1 LIKE {quote}\
                    OR admin_code1 LIKE {quote}\
                    OR admin_name2 LIKE {quote}\
                    OR admin_code2 LIKE {quote}\
                    OR admin_name3 LIKE {quote}\
                    OR admin_code3 LIKE {quote})".format(quote=quote)
        sql_statement += condition
        if (i + 1) < len(item):
            sql_statement += " and"
    # Get the rows contains the string user typed in
    rows = db.execute(sql_statement)
    # Output places as JSON
    return jsonify(rows)


@app.route("/update")
def update():
    """Find up to 10 places within view"""

    # Ensure parameters are present
    if not request.args.get("sw"):
        raise RuntimeError("missing sw")
    if not request.args.get("ne"):
        raise RuntimeError("missing ne")

    # Ensure parameters are in lat,lng format
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("sw")):
        raise RuntimeError("invalid sw")
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("ne")):
        raise RuntimeError("invalid ne")

    # Explode southwest corner into two variables
    sw_lat, sw_lng = map(float, request.args.get("sw").split(","))

    # Explode northeast corner into two variables
    ne_lat, ne_lng = map(float, request.args.get("ne").split(","))

    # Find 10 cities within view, pseudorandomly chosen if more within view
    if sw_lng <= ne_lng:

        # Doesn't cross the antimeridian
        rows = db.execute("""SELECT * FROM places
                          WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude AND longitude <= :ne_lng)
                          GROUP BY country_code, place_name, admin_code1
                          ORDER BY RANDOM()
                          LIMIT 10""",
                          sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)

    else:

        # Crosses the antimeridian
        rows = db.execute("""SELECT * FROM places
                          WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude OR longitude <= :ne_lng)
                          GROUP BY country_code, place_name, admin_code1
                          ORDER BY RANDOM()
                          LIMIT 10""",
                          sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)

    # Output places as JSON
    return jsonify(rows)
