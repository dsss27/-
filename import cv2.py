import cv2
import numpy as np

def correct_skew(image_path, output_path):
    image = cv2.imread(image_path)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (5, 5), 0)
    edges = cv2.Canny(blurred, 50, 150)
    contours, _ = cv2.findContours(edges, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
    all_points = np.vstack([contour.reshape(-1, 2) for contour in contours])
    rect = cv2.minAreaRect(all_points)
    angle = rect[-1]
    if angle < -45:
        angle += 90
    (h, w) = image.shape[:2]
    center = (w // 2, h // 2)
    rotation_matrix = cv2.getRotationMatrix2D(center, angle, 1.0)
    rotated = cv2.warpAffine(image, rotation_matrix, (w, h), flags=cv2.INTER_CUBIC, borderMode=cv2.BORDER_REPLICATE)
    cv2.imwrite(output_path, rotated)
    print(f"Изображение сохранено: {output_path}")
input_image = "/mnt/data/image.png"
output_image = "/mnt/data/corrected_image.png"
correct_skew(input_image, output_image)
