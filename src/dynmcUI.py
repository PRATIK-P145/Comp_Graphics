import cv2
import mediapipe as mp
import numpy as np

# Initialize Mediapipe Hand tracking
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(max_num_hands=2, min_detection_confidence=0.7)
mp_draw = mp.solutions.drawing_utils

# Define initial position of Calculator UI
calc_x, calc_y = 50, 50  # Initial position

# Calculator size
calc_width, calc_height = 300, 400

# Open webcam
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Flip the frame for natural view
    frame = cv2.flip(frame, 1)
    h, w, c = frame.shape

    # Convert to RGB
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    # Detect hands
    result = hands.process(rgb_frame)

    if result.multi_hand_landmarks:
        for hand_landmarks, hand_info in zip(result.multi_hand_landmarks, result.multi_handedness):
            label = hand_info.classification[0].label
            if label == "Left":  # Check for left hand
                # Get wrist or palm center position
                wrist_x, wrist_y = int(hand_landmarks.landmark[0].x * w), int(hand_landmarks.landmark[0].y * h)

                # Smoothly move calculator UI towards palm
                calc_x = int(0.8 * calc_x + 0.2 * wrist_x)  # Smoothing for X-axis
                calc_y = int(0.8 * calc_y + 0.2 * wrist_y)  # Smoothing for Y-axis

    # Draw Calculator UI (Mocked as a rectangle for now)
    cv2.rectangle(frame, (calc_x, calc_y), (calc_x + calc_width, calc_y + calc_height), (0, 255, 0), 2)
    cv2.putText(frame, "Calculator UI", (calc_x + 15, calc_y + 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    # Display the frame
    cv2.imshow("Virtual Calculator", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
