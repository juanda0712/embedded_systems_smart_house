from flask import Flask, render_template, jsonify, request
import subprocess


app = Flask(__name__)

estado = {
    "luces": [False, False, False, False, False],
    "puertas": [False, False, False, False]
}

def encender_luz(index):
    subprocess.run(["bins/outputs/bin/signal_sender", str(index), "on"])

def apagar_luz(index):
    subprocess.run(["bins/outputs/bin/signal_sender", str(index), "off"])

def leer_puerta(index):
    resultado = subprocess.run(["bins/inputs/bin/signal_verifier", str(index)])
    estado = resultado.returncode
    return estado  # 0 = cerrada, 1 = abierta


def tomar_foto():
    subprocess.run(["bins/photo/bin/photo"])


@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api/estado', methods=["GET", "POST"])
def obtener_estado():
    if request.method == "POST":
        data = request.json
        luces = data["luces"]
        for i, valor in enumerate(luces):
            if valor:
                encender_luz(i)
            else:
                apagar_luz(i)
    luces = []  
    puertas = []
    for i in range(4):  
        estado_puerta = leer_puerta(i)
        puertas.append(True if estado_puerta == 1 else False)

    return jsonify({
        "luces": luces,  
        "puertas": puertas
    })


@app.route('/api/camara')
def camara():
    tomar_foto()
    return app.send_static_file('jardin.jpg')


if __name__ == '__main__':
    app.run(debug=True)
