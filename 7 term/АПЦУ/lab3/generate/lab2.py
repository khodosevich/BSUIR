from itertools import product

output_file = "test2.txt"


def generate_demux_data(file_path):
    with open(file_path, "w") as f:
        for inputs in product("01", repeat=6):
            f.write("".join(inputs) + "\n")

    print(f"Тестовые данные успешно записаны в файл: {file_path}")


generate_demux_data(output_file)
