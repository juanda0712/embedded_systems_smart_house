from flask import Blueprint, render_template, request, redirect, url_for, session

auth = Blueprint("auth", __name__)

usuarios = {
    "admin": "1234"
}

@auth.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        usuario = request.form.get("usuario")
        password = request.form.get("password")
        if usuario in usuarios and usuarios[usuario] == password:
            session["usuario"] = usuario
            return redirect(url_for("index"))
        else:
            return render_template("login.html", error="Usuario o contraseña incorrecta")
    return render_template("login.html")

@auth.route("/logout")
def logout():
    session.pop("usuario", None)
    return redirect(url_for("auth.login"))
