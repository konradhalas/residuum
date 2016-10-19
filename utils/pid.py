import argparse

def line_range(sensors_count):
    return ((sensors_count * 1000 - 1000) / 2)

def pid(error, last_error, kp, kd):
    return int(kp * error + kd * (error - last_error))

def warn(content, should_warn, template):
    rendered =  template.format(content)
    if should_warn:
        return '\033[91m' + rendered + '\033[0m'
    return rendered

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("--speed", type=int, required=True)
    parser.add_argument("--sensors", type=int, required=True)
    parser.add_argument("--kp", type=float, required=True)
    parser.add_argument("--kd", type=int, required=True)
    args = parser.parse_args()

    for line_over in range(args.sensors):
        error = line_over * 1000 - line_range(args.sensors)
        pid_delta = pid(
            error=error,
            last_error=error,
            kp=args.kp,
            kd=args.kd,
        )
        print("{} = error: {:5d}, delta: {:6.1f}, motors: {}, {}".format(
            line_over + 1,
            error,
            pid_delta,
            warn(args.speed + pid_delta, not(-255 <= (args.speed + pid_delta) <= 255), '{:3d}') ,
            warn(args.speed - pid_delta, not(-255 <= (args.speed - pid_delta) <= 255), '{:3d}') ,
        ))
