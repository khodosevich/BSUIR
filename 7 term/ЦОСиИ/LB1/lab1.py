import cv2
import numpy as np
from matplotlib import pyplot as plt

# Путь к изображению
image_path = r'.\1725544579789.jpg'
image = cv2.imread(image_path)

if image is None:
    print("Ошибка: не удалось загрузить изображение. Проверьте путь.")
else:
    hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    lower_blue = np.array([100, 150, 50])
    upper_blue = np.array([140, 255, 255])

    lower_green = np.array([40, 50, 50])
    upper_green = np.array([90, 255, 255])

    mask_blue = cv2.inRange(hsv, lower_blue, upper_blue)
    mask_green = cv2.inRange(hsv, lower_green, upper_green)

    combined_mask = cv2.bitwise_or(mask_blue, mask_green)

    result = cv2.bitwise_and(image, image, mask=combined_mask)

    gray_result = cv2.cvtColor(result, cv2.COLOR_BGR2GRAY)

    _, binary_result = cv2.threshold(gray_result, 1, 255, cv2.THRESH_BINARY)

    contours, _ = cv2.findContours(binary_result, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    min_contour_area = 500

    def is_square(approx):
        return len(approx) == 4 and cv2.isContourConvex(approx)

    def is_circle(contour):
        area = cv2.contourArea(contour)
        perimeter = cv2.arcLength(contour, True)
        return (perimeter != 0) and (0.7 < 4 * np.pi * (area / (perimeter ** 2)) < 1.2)

    def is_hexagon(approx):
        return len(approx) == 6 and cv2.isContourConvex(approx)

    filtered_contours = []
    for contour in contours:
        if cv2.contourArea(contour) > min_contour_area:
            approx = cv2.approxPolyDP(contour, 0.02 * cv2.arcLength(contour, True), True)
            if is_circle(contour) or is_square(approx) or is_hexagon(approx):
                filtered_contours.append(contour)

    empty_image = np.zeros_like(image)

    cv2.drawContours(empty_image, filtered_contours, -1, (255, 255, 255), 2)  # Белые контуры

    plt.figure(figsize=(12, 6))

    plt.subplot(1, 2, 1)
    plt.imshow(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
    plt.title('Оригинальное изображение')

    plt.subplot(1, 2, 2)
    plt.imshow(cv2.cvtColor(empty_image, cv2.COLOR_BGR2RGB))
    plt.title('Контуры кругов, квадратов и шестиугольников')

    plt.tight_layout()
    plt.show()


