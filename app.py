from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/endpoint', methods=['POST'])
def receive_data():
    data = request.get_json()
    if data:
        print(f"Received data: {data}")
        return jsonify({"status": "success", "data_received": data}), 200
    else:
        return jsonify({"status": "error", "message": "No data received"}), 400

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)