from itertools import product

output_file = "test.txt"


def generate_demux_data(file_path):
    with open(file_path, "w") as f:
        for inputs in product("01", repeat=6):
            a0, a1, a2, ne1, ne2, e3 = inputs

            if ne1 == "1" or ne2 == "1" or e3 == "0":
                outputs = ["0"] * 8
            else:
                outputs = ["0"] * 8
                address = int(f"{a2}{a1}{a0}", 2)
                outputs[address] = "1"

            f.write("".join(inputs + tuple(outputs)) + "\n")

    print(f"Тестовые данные успешно записаны в файл: {file_path}")


generate_demux_data(output_file)
