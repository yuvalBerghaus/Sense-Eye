from flask import Flask, request

app = Flask(__name__)


@app.route('/save_id')
def save_id():
    color_band = request.args.get('color_band')
    ip = request.args.get('ip')
    print("ip is = " + ip)
    print("color_band is = " + color_band)
    # Do something with the received data
    return "Data received"


if __name__ == '__main__':
    app.run(host='192.168.14.3', port=5000, threaded=False)
