from flask import Flask, render_template, jsonify, request
import subprocess

app = Flask(__name__)

# Estado SIMULADO en memoria
estado = {
    "luces": [False, False, False, False, False],  # 5 luces
}

def encender_luz(index):
    subprocess.run(["bins/outputs/bin/signal_sender", str(index), "on"])

def apagar_luz(index):
    subprocess.run(["bins/outputs/bin/signal_sender", str(index), "off"])

def leer_puerta(index):
    resultado = subprocess.run(["bins/inputs/bin/signal_verifier", str(index)])
    estado_puerta = resultado.returncode
    return estado_puerta  # 0=cerrada, 1=abierta

def tomar_foto():
    subprocess.run(["bins/photo/bin/photo"])

@app.route('/')
def index():
    return render_template('index.html')

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
    puertas_estado = []
    for i in range(4):  # 4 puertas
        puerta_abierta = leer_puerta(i)
        puertas_estado.append(True if puerta_abierta == 1 else False)
    return jsonify(puertas_estado)

@app.route('/api/camara')
def camara():
    tomar_foto()
    return app.send_static_file('picture.jpeg')

if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True)
