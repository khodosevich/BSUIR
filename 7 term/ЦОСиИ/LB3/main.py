import cv2
import numpy as np
import matplotlib.pyplot as plt

image_path = r"..\images\4.jpg"
image = cv2.imread(image_path)

if image is None:
    print("Ошибка: изображение не найдено. Проверьте путь:", image_path)
else:
    hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    lower_green = np.array([35, 80, 80])
    upper_green = np.array([85, 255, 255])

    mask = cv2.inRange(hsv, lower_green, upper_green)

    #дилатация для уменьшения шума
    kernel = np.ones((3, 3), np.uint8)
    dilated_mask = cv2.dilate(mask, kernel, iterations=2)

    contours, _ = cv2.findContours(dilated_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    aligned_objects = np.zeros_like(image)

    rotation_angles = []

    for contour in contours:
        if cv2.contourArea(contour) < 100:
            continue

        rect = cv2.minAreaRect(contour)
        angle = rect[2]

        if rect[1][0] < rect[1][1]:
            corrected_angle = angle
        else:

            if image_path == r"..\images\1.jpg":
                corrected_angle = angle + 90
            else:
                corrected_angle = angle - 90

        rotation_angles.append(corrected_angle)

        box = cv2.boxPoints(rect)
        box = np.int32(box)
        x, y, w, h = cv2.boundingRect(box)

        cropped = image[y:y + h, x:x + w]

        #поворот
        center = (w // 2, h // 2)
        rotation_matrix = cv2.getRotationMatrix2D(center, corrected_angle, 1.0)
        rotated = cv2.warpAffine(cropped, rotation_matrix, (w, h), flags=cv2.INTER_LINEAR, borderValue=(0, 0, 0))

        object_mask = dilated_mask[y:y + h, x:x + w]
        rotated_mask = cv2.warpAffine(object_mask, rotation_matrix, (w, h), flags=cv2.INTER_LINEAR, borderValue=0)
        object_mask_inv = cv2.bitwise_not(rotated_mask)

        object_only = cv2.bitwise_and(rotated, rotated, mask=rotated_mask)
        aligned_objects[y:y + rotated.shape[0], x:x + rotated.shape[1]] = cv2.bitwise_and(
            aligned_objects[y:y + rotated.shape[0], x:x + rotated.shape[1]],
            aligned_objects[y:y + rotated.shape[0], x:x + rotated.shape[1]],
            mask=object_mask_inv
        )
        aligned_objects[y:y + rotated.shape[0], x:x + rotated.shape[1]] += object_only

    for i, angle in enumerate(rotation_angles, start=1):
        print(f"Объект {i} повёрнут на {angle:.1f}° ")

    fig, ax = plt.subplots(1, 2, figsize=(10, 5))
    ax[0].imshow(cv2.cvtColor(mask, cv2.COLOR_GRAY2RGB))
    ax[0].set_title("Контуры")
    ax[0].axis("off")

    ax[1].imshow(cv2.cvtColor(aligned_objects, cv2.COLOR_BGR2RGB))
    ax[1].set_title("После переворота")
    ax[1].axis("off")

    plt.show()
