def liang_barsky(x_0, y_0, x_1, y_1, x_min, y_min, x_max, y_max):
    # Рассчитываем изменения координат
    dx = x_1 - x_0
    dy = y_1 - y_0

    # Инициализируем параметры u1 и u2
    u1 = 0
    u2 = 1

    # Создаем массивы p и q
    p = [-dx, dx, -dy, dy]
    q = [x_0 - x_min, x_max - x_0, y_0 - y_min, y_max - y_0]

    # Проходим по массивам p и q
    for i in range(4):
        if p[i] == 0:
            # Линия параллельна отсекающей координатной оси
            if q[i] < 0:
                # Линия полностью слева/сверху от окна
                return None
        else:
            # Рассчитываем параметр u
            u = q[i] / p[i]
            # Обновляем u1 и u2 в зависимости от направления отсечения
            if p[i] < 0:
                u1 = max(u, u1)
            else:
                u2 = min(u, u2)
    if u1 > u2:
        # Линия полностью за пределами окна
        return None

    # Рассчитываем координаты отсеченного отрезка
    x1_clip = x_0 + u1 * dx
    y1_clip = y_0 + u1 * dy
    x2_clip = x_0 + u2 * dx
    y2_clip = y_0 + u2 * dy

    return x1_clip, y1_clip, x2_clip, y2_clip


def cyrus_beck(x_a, y_a, x_b, y_b, polygon):
    # Преобразуем координаты многоугольника в список точек
    p = []
    for i in range(0, len(polygon), 2):
        p.append([polygon[i], polygon[i + 1]])

    # Инициализируем параметры t_min и t_max
    t_min = 0
    t_max = 1

    # Проходим по ребрам многоугольника
    for i in range(len(p) - 1):
        # Вычисляем векторное произведение
        v1 = (p[i + 1][0] - p[i][0]) * (y_b - y_a) - (p[i + 1][1] - p[i][1]) * (x_b - x_a)
        v2 = (p[i + 1][0] - p[i][0]) * (y_a - p[i][1]) - (p[i + 1][1] - p[i][1]) * (x_a - p[i][0])

        if v1 > 0:
            # Линия входит в многоугольник
            temp = -v2 / v1
            if temp > t_min:
                t_min = temp
        else:
            # Линия выходит из многоугольника
            temp = -v2 / v1
            if temp < t_max:
                t_max = temp
        if t_min > t_max:
            # Линия полностью вне многоугольника
            break

    # Рассчитываем координаты отсеченного отрезка
    x1_clip = x_a + (x_b - x_a) * t_min
    y1_clip = y_a + (y_b - y_a) * t_min
    x2_clip = x_a + (x_b - x_a) * t_max
    y2_clip = y_a + (y_b - y_a) * t_max

    return x1_clip, y1_clip, x2_clip, y2_clip
