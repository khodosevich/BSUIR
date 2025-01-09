import cv2
import numpy as np


def up_scale(image):
    scale_percent = 20 if image_path != 'dataset/11.jpg' else 40
    width = int(image.shape[1] * scale_percent / 100)
    height = int(image.shape[0] * scale_percent / 100)
    dim = (width, height)
    image = cv2.resize(image, dim, interpolation=cv2.INTER_AREA)
    return image


def mask_blue(image):
    lower_blue = np.array([100, 150, 200]) if image_path == 'da/11.jpg' else np.array([100, 150, 200])
    upper_blue = np.array([140, 255, 255])
    hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv_image, lower_blue, upper_blue)
    blue_masked_image = cv2.bitwise_and(image, image, mask=mask)
    return blue_masked_image


def apply_minimal_filter(image, ksize1, ksize2):
    if len(image.shape) == 3:
        gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    else:
        gray_image = image
    kernel_min = np.ones((ksize1, ksize2), np.uint8)
    filtered_image = cv2.erode(gray_image, kernel_min)
    return filtered_image


def apply_median_filter(image, ksize):
    if len(image.shape) == 3:
        gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    else:
        gray_image = image
    filtered_image = cv2.medianBlur(gray_image, ksize)
    return filtered_image


def apply_Sobel_operator(image, ksize):
    if len(image.shape) == 3:
        gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    else:
        gray_image = image

    sobel_x = cv2.Sobel(gray_image, cv2.CV_64F, 1, 0, ksize=ksize)
    sobel_y = cv2.Sobel(gray_image, cv2.CV_64F, 0, 1, ksize=ksize)
    sobel_combined = cv2.magnitude(sobel_x, sobel_y)
    sobel_image = cv2.convertScaleAbs(sobel_combined)
    return sobel_image


def apply_dilation(image, ksize1, ksize2):
    kernel = np.ones((ksize1, ksize2), np.uint8)
    dilated_image = cv2.dilate(image, kernel, iterations=1)
    return dilated_image


def search_the_contours(image):
    blurred = cv2.GaussianBlur(image, (11, 5), 0)
    edges = cv2.Canny(blurred, 50, 150)
    contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    contour_image = image.copy()
    cv2.drawContours(contour_image, contours, -1, (255, 255, 255), 1)
    return contour_image


def mask_gray(image):
    threshold_value = 35
    _, gray_masked_image = cv2.threshold(image, threshold_value, 255, cv2.THRESH_BINARY)
    return gray_masked_image


def cluster_objects(image, min_corners=4, min_perimeter=22, min_area=1, area_threshold=1000):
    result_image = image.copy()
    blurred = cv2.GaussianBlur(image, (3, 3), 0)
    edges = cv2.Canny(blurred, 50, 150)
    contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    results = []
    small_contours = []
    areas = []

    for contour in contours:
        area = calculate_area(contour)
        if area >= area_threshold:
            areas.append(area)
    areas.sort()
    #avg_area = np.mean(areas) if areas else 0
    #area_to_eliminate = avg_area
    area_to_eliminate = areas[len(areas)-1]/2

    for contour in contours:
        peri = calculate_perimeter(contour)
        approx = calculate_corners_number(contour, 0.02 * peri)
        corner_count = len(approx)
        area = calculate_area(contour)

        if (area < area_threshold or area < area_to_eliminate) and peri >= min_perimeter:
            small_contours.append((contour, corner_count))
            continue

        if corner_count >= min_corners and peri >= min_perimeter and area >= min_area:
            results.append({
                'corners': corner_count,
                'perimeter': peri,
                'area': area
            })

            color = get_color_by_corners(corner_count)

            if len(result_image.shape) == 2:
                result_image = cv2.cvtColor(result_image, cv2.COLOR_GRAY2BGR)

            cv2.drawContours(result_image, [contour], -1, color, thickness=cv2.FILLED)
        else:
            cv2.drawContours(result_image, [contour], -1, (0, 0, 0), thickness=2)

    if small_contours:
        minimal_corners = calculate_minimal_corners(small_contours)

        color = get_color_by_corners(minimal_corners)

        for contour, _ in small_contours:
            if len(result_image.shape) == 2:
                result_image = cv2.cvtColor(result_image, cv2.COLOR_GRAY2BGR)

            cv2.drawContours(result_image, [contour], -1, color, thickness=cv2.FILLED)

    return results, result_image


def calculate_area(contour):
    """Вычисляет площадь контура с помощью формулы Гаусса."""
    # Преобразуем контур в массив точек (каждая точка — это (x, y))
    points = contour.reshape(-1, 2)

    # Инициализируем переменные для сумм
    sum1 = 0.0
    sum2 = 0.0

    # Применяем формулу Гаусса (Shoelace)
    for i in range(len(points)):
        x1, y1 = points[i]
        x2, y2 = points[(i + 1) % len(points)]  # Следующая точка (циклический переход для замыкания контура)
        sum1 += x1 * y2
        sum2 += y1 * x2

    # Площадь — это половина разности между суммами
    area = 0.5 * abs(sum1 - sum2)
    return area


def calculate_corners_number(contour, epsilon):
    # Преобразование контура в удобный формат
    points = contour.reshape(-1, 2)

    # Применение алгоритм Рамера-Дугласа-Пекера
    approx = rdp(points, epsilon)

    # Возвращает аппроксимированный контур в исходный формат
    return approx.reshape(-1, 1, 2).astype(np.int32)


def rdp(points, epsilon):
    # Находим точку с максимальным расстоянием до линии, соединяющей начало и конец
    start, end = points[0], points[-1]
    max_distance = 0
    index = 0
    for i in range(1, len(points) - 1):
        dist = distance_to_line(points[i], start, end)
        if dist > max_distance:
            max_distance = dist
            index = i

    # Если максимальное расстояние больше порога, рекурсивно упрощаем
    if max_distance > epsilon:
        # Рекурсивно упрощаем первую и вторую половину
        first_half = rdp(points[:index + 1], epsilon)
        second_half = rdp(points[index:], epsilon)

        # Комбинируем результаты, удаляя дублирующую точку
        return np.vstack((first_half[:-1], second_half))
    else:
        # Если все точки находятся на линии, оставляем только начальную и конечную точки
        return np.array([start, end])


def distance_to_line(point, start, end):  # Вычисляет расстояние от точки до прямой, проходящей через точки start и end

    if np.array_equal(start, end):
        return np.linalg.norm(point - start)

    # Преобразуем двумерные векторы в трехмерные, добавив координату Z = 0
    start_3d = np.array([start[0], start[1], 0])
    end_3d = np.array([end[0], end[1], 0])
    point_3d = np.array([point[0], point[1], 0])

    # Вычисляем векторное произведение для трехмерных векторов
    return np.abs(np.cross(end_3d - start_3d, start_3d - point_3d)[-1] / np.linalg.norm(end_3d - start_3d))


def calculate_perimeter(contour):  # Вычисляет периметр (длину) контура.
    perimeter = 0.0

    # Преобразуем контур в массив точек (каждая точка — это (x, y))
    points = contour.reshape(-1, 2)

    # Проходим по всем точкам и суммируем расстояния между ними
    for i in range(len(points)):
        next_index = (i + 1) % len(points)  # Следующая точка (с циклическим переходом)
        distance = np.linalg.norm(points[i] - points[next_index])  # Расстояние между соседними точками
        perimeter += distance

    return perimeter


def calculate_minimal_corners(small_contours):
    total_corners = sum(corner_count for _, corner_count in small_contours)
    p = len(small_contours)
    minimum_corners = total_corners - 2 * (p - 1)
    return minimum_corners


def get_color_by_corners(corner_count):
    if corner_count == 4:
        color = (0, 0, 255)  # Красный
    elif corner_count == 5:
        color = (0, 165, 255)  # Оранжевый
    elif corner_count == 6:
        color = (0, 255, 255)  # Жёлтый
    elif corner_count == 7:
        color = (0, 255, 0)  # Зелёный
    elif corner_count == 8:
        color = (255, 255, 0)  # Голубой
    elif corner_count == 9:
        color = (255, 0, 0)  # Синий
    elif corner_count > 9:
        color = (255, 0, 255)  # Фиолетовый
    else:
        color = (255, 255, 255)  # Белый
    return color


image_path = '../images/1.jpg'

#if image_path == 'dataset/2.jpg' or image_path == 'dataset/4.jpg' or image_path == 'dataset/6.jpg':
   # median_ksize = 5
#else:

median_ksize = 5

image = cv2.imread(image_path)

if image is None:
    print("Ошибка: не удалось загрузить изображение.")
else:
    image = up_scale(image)

    image = mask_blue(image)

    image = apply_Sobel_operator(image, 3)

    image = apply_dilation(image, 3, 3)

    image = apply_median_filter(image, median_ksize)

    image = apply_minimal_filter(image, 3, 3)

    image = mask_gray(image)

    image = search_the_contours(image)

    # cv2.imshow('Contoured_image', image)

    corner_counts, res_image = cluster_objects(image)

    for i, count in enumerate(corner_counts):
        print(f"Объект {i + 1}: {count}")

    cv2.imshow('Colored_image', res_image)

    cv2.waitKey(0)
    cv2.destroyAllWindows()