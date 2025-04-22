from flask import Flask, render_template, jsonify

app = Flask(__name__)

# Estado simulado
estado = {
    "luces": [False, False, False, False, False],
    "puertas": [False, False, False, False]
}

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api/estado')
def obtener_estado():
    return jsonify(estado)

if __name__ == '__main__':
    app.run(debug=True)
