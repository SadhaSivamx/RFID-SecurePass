def Capturee():
    import cv2
    cap = cv2.VideoCapture(0)
    ret, frame = cap.read()
    cv2.imwrite('capture.png', frame)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
