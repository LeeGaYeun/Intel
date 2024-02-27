import cv2
import numpy as np
import sqlite3
import socket
import os
import time
import threading

global turn
turn = 0


# 사용자의 홈 디렉토리 경로 가져오기
home_dir = os.path.expanduser('C:/Users/EMBEDDED/source/repos/Intel/OpenCV/eleprj')
#home_dir = os.path.expanduser('c:/Users/EMBEDDED/Desktop/[OpenCV]엘리베이터')
db_path = os.path.join(home_dir, 'faces.db')

# 얼굴 검출을 위한 Haar 캐스케이드 분류기 경로
cascade_path = cv2.data.haarcascades + 'haarcascade_frontalface_default.xml'

# 얼굴 검출을 위한 분류기 생성
face_cascade = cv2.CascadeClassifier(cascade_path)

# SQLite 데이터베이스 연결
conn = sqlite3.connect('faces.db')
c = conn.cursor()

# 서버 주소와 포트 번호
server_address = '10.10.23.202'
server_port = 5001

# 소켓 생성
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 서버에 연결
client_socket.connect((server_address, server_port))

# 데이터베이스에서 얼굴 정보 가져오기
c.execute("SELECT name, room, landmarks FROM faces")
records = c.fetchall()

# DB에 저장된 사용자 정보 출력
print("DB에 저장된 사용자 정보:")
for record in records:
    name, room, landmarks_str = record
    print(f"이름: {name}, 호수: {room}")

# 동영상 캡처 객체 생성
cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)

# 서버로부터 메시지 수신하는 함수
def receive_message():
    global turn
    while True:        
            # 서버로부터 메시지 수신
        message = client_socket.recv(1024)
        if not message:
            break
        print("서버로부터 수신한 메시지:", message.decode())
        
        turn = int(message.decode())
        
        

# 메시지 수신을 위한 스레드 시작
receive_thread = threading.Thread(target=receive_message)
receive_thread.start()

while True:
    # 프레임 읽기
    ret, frame = cap.read()

    if not ret:
        break

    # 좌우 반전
    frame = cv2.flip(frame, 1)

    # 그레이스케일 변환
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # 얼굴 검출
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))
    
    if turn == 0:
        if len(faces) == 0:# 얼굴이 발견되지 않은 경우
                message = "NOT!!!"
                client_socket.sendall(message.encode())
                #continue
                    
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)

        # 얼굴 특징점 추출
        roi_gray = gray[y:y+h, x:x+w]
        roi_gray_resized = cv2.resize(roi_gray, (64, 128))
        hog = cv2.HOGDescriptor()
        landmarks = hog.compute(roi_gray_resized)

        # SQLite DB에서 얼굴 정보 가져오기
        c.execute("SELECT name, room, landmarks FROM faces")
        records = c.fetchall()
        

        # 얼굴 정보 비교
        for record in records:
            name, room, landmarks_db_str = record
            landmarks_db = np.array(eval(landmarks_db_str))  # 문자열을 다시 numpy 배열로 변환
            # 얼굴 비교 (유클리디안 거리 기반)
            similarity = np.linalg.norm(landmarks - landmarks_db)  # 유클리디안 거리 계산
            threshold = 7  # 임계값 설정
            if similarity < threshold:
                # 일치하는 얼굴이면 이름과 호수 출력
                cv2.putText(frame, f'{name}, {room}', (x, y - 30), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2, cv2.LINE_AA)
                
                # 호수에서 첫 번째 숫자 추출
                room_number = ''.join(filter(str.isdigit, room))
                print(turn)
                if turn == 0:
                    # 서버에 보낼 메시지
                    message = f"{room_number}"
                    # 메시지 전송
                    client_socket.sendall(message.encode())
                    break
        else:  # 사각형만 존재할 때
            if turn == 0:
                message = "NOT!!!"
                client_socket.sendall(message.encode())
                continue
        break  # 일치하는 얼굴을 찾은 경우 루프 종료

    # 화면에 출력
    cv2.imshow('Video', frame)

    key = cv2.waitKey(1)
    if key == 27:
        print("ESC is break")  
        break

# 종료
cap.release()
cv2.destroyAllWindows()
conn.close()
client_socket.close()  # 소켓 닫기
