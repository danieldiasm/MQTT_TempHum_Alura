import paho.mqtt.subscribe as subscribe

print("Esperando a mensagem!")
msg = subscribe.simple("top/term", hostname="192.168.2.116", msg_count=1)
print("Mensagem: " + str(msg.payload))