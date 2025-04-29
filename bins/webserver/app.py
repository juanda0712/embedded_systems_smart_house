from flask import Flask, render_template, jsonify, request, session, redirect, url_for
import subprocess
import os
import json
from auth import auth

# Leer configuración local
CONFIG_FILE = "config_local.json"
if os.path.exists(CONFIG_FILE):
    with open(CONFIG_FILE) as f:
        config = json.load(f)
    BASE_DIR = config.get("BASE_DIR", ".")
else:
    BASE_DIR = "."

app = Flask(__name__,
            static_folder=os.path.join(BASE_DIR, 'static'),
            template_folder=os.path.join(BASE_DIR, 'templates'))
app.secret_key = 'clave-secreta'  

app.register_blueprint(auth)

# Estado SIMULADO en memoria
estado = {
    "luces": [False, False, False, False, False],
}

mapa_luces = [5, 6, 13, 19, 26]
mapa_puertas = [2, 3, 4, 15]

def encender_luz(index):
    pin = mapa_luces[index]
    subprocess.run(["signal_sender", str(pin), "1"])

def apagar_luz(index):
    pin = mapa_luces[index]
    subprocess.run(["signal_sender", str(pin), "0"])

def leer_puerta(index):
    pin = mapa_puertas[index]
    resultado = subprocess.run(["signal_verifier", str(pin)])
    return resultado.returncode  # 0 = cerrada, 1 = abierta

def tomar_foto():
    subprocess.run(["usr/bin/photo"])

@app.route('/')
def index():
    if "usuario" not in session:
        return redirect(url_for("auth.login"))
    return render_template("index.html")

@app.route('/api/luces', methods=["GET", "POST"])
def luces():
    global estado
    if request.method == "POST":
        data = request.json
        estado["luces"] = data["luces"]
        for i, valor in enumerate(estado["luces"]):
            if valor:
                encender_luz(i)
            else:
                apagar_luz(i)
    return jsonify(estado["luces"])

@app.route('/api/puertas', methods=["GET"])
def puertas():
    return jsonify([
        leer_puerta(i) == 1 for i in range(4)
    ])

@app.route('/api/camara')
def camara():
    tomar_foto()
    return app.send_static_file('picture.jpg')

if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True)
