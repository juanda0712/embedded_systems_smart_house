from flask import Flask, render_template, jsonify, request

app = Flask(__name__)

estado = {
    "luces": [False, False, False, False, False],
    "puertas": [False, False, False, False]
}

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api/estado', methods=["GET", "POST"])
def obtener_estado():
    global estado
    if request.method == "POST":
        datos = request.json
        estado = datos
    return jsonify(estado)

if __name__ == '__main__':
    app.run(debug=True)
