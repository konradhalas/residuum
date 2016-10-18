def line_range(sensors_count):
    return ((sensors_count * 1000 - 1000) / 2)

def pid(error, last_error, kp, kd):
    return int(kp * error + kd * (error - last_error))


if __name__ == '__main__':
    base_motors_speed = 120
    sensors_count = 8
    kp = 0.04
    kd = 1

    for line_over in range(sensors_count):
        error = line_over * 1000 - line_range(sensors_count)
        pid_delta = pid(
            error=error,
            last_error=error,
            kp=kp,
            kd=kd,
        )
        print("{} = error: {:5d}, delta: {:6.1f}, motors: {:3d}, {:3d}".format(
            line_over + 1,
            error,
            pid_delta,
            base_motors_speed + pid_delta,
            base_motors_speed - pid_delta,
        ))
