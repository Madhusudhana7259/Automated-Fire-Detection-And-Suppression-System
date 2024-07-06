from ultralytics import YOLO
import cvzone
import cv2
import math
import serial
import time
arduino = serial.Serial('com12', 300)  # Create Serial port object called arduinoSerialData



cap = cv2.VideoCapture(0)
model = YOLO('60.pt')       # Load The Model


classnames = ['fire']

while True:
    ret, frame = cap.read()
    frame = cv2.resize(frame, (640, 480)) # Resizing the Frame to required Format
    result = model(frame, stream=True)


    for info in result: # Loop for identifying the Probability of Fire within the box
        boxes = info.boxes

        for box in boxes:
            confidence = box.conf[0]
            confidence = math.ceil(confidence * 100)
            Class = int(box.cls[0])
            if confidence > 50:
                x1, y1, x2, y2 = box.xyxy[0]
                x1, y1, x2, y2 = int(x1), int(y1), int(x2), int(y2)
                cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 0, 255), 5)
                cvzone.putTextRect(frame, f'{classnames[Class]} {confidence}%', [x1 + 8, y1 + 100],
                                   scale=1.5, thickness=2)

                arduino.write(bytes([1])) # Transmitting the Byte value 1 when fire confidence is greater than Threshold
                time.sleep(3)

            arduino.write(bytes([0]))
        arduino.write(bytes([0]))


    cv2.imshow('frame', frame)
    if cv2.waitKey(1) == 27:
        break