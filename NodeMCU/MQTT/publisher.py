import paho.mqtt.client as mqtt

client = mqtt.Client()
client.connect("192.168.2.116")
client.publish("lab/temperatura", "25")
print("Mensagem enviada!")
client.disconnect()