import random

file_path = "test3.txt"

with (open(file_path, 'w') as test_file):
    QA, QB, QC, QD = '0', '1', '0', '1'
    QA_t, QB_t, QC_t, QD_t = '0', '1', '0', '1'
    RCO = '1'
    CLK = '1'
    UD = '1'

    number = 10
    line = "00001010101011\n"
    test_file.write(line)

    clk = '1'
    ent = '0'
    enp = '0'
    rco = '1'
    ud = '1'

    for i in range(50):
        clk = '1' if clk == '0' else '0'

        if enp == '0' and ent == '0':
            if clk == '0':
                bin_number = bin(number)[2:].zfill(4)
                check_result = bin_number[::-1]
                line = f"11{enp}{ent}{clk}0101{check_result}{rco}\n"
                test_file.write(line)
            if clk == '1':
                if number == 15:
                    number = -1

                if number == 14 and ent == '0':
                    rco = '0'
                else:
                    rco = '1'

                number += 1
                bin_number = bin(number)[2:].zfill(4)
                check_result = bin_number[::-1]
                line = f"11{enp}{ent}{clk}0101{check_result}{rco}\n"
                test_file.write(line)

    ud = '0'
    for i in range(50):
        clk = '1' if clk == '0' else '0'

        if enp == '0' and ent == '0':
            if clk == '0':
                bin_number = bin(number)[2:].zfill(4)
                check_result = bin_number[::-1]
                line = f"10{enp}{ent}{clk}0101{check_result}{rco}\n"
                test_file.write(line)
            if clk == '1':
                if number == 0:
                    number = 16

                if number == 1 and ent == '0':
                    rco = '0'
                else:
                    rco = '1'

                number -= 1
                bin_number = bin(number)[2:].zfill(4)
                check_result = bin_number[::-1]
                line = f"10{enp}{ent}{clk}0101{check_result}{rco}\n"
                test_file.write(line)

    for _ in range(2048):

        ENT, ENP, LOAD = [str(random.randint(0, 1)) for _ in range(3)]

        UD = '1' if random.random() < 0.5 else '0'

        A, B, C, D = [str(random.randint(0, 1)) for _ in range(4)]
        CLK = '1' if CLK == '0' else '0'

        if LOAD == '0':
            if CLK == '1':
                QA_t, QB_t, QC_t, QD_t = A, B, C, D
                QA, QB, QC, QD = A, B, C, D
        else:
            if ENT == '0' and ENP == '0':
                if CLK == '1':
                    if UD == '1':
                        if QA_t == '0':
                            QA_t = '1'
                        else:
                            QA_t = '0'
                            if QB_t == '0':
                                QB_t = '1'
                            else:
                                QB_t = '0'
                                if QC_t == '0':
                                    QC_t = '1'
                                else:
                                    QC_t = '0'
                                    if QD_t == '0':
                                        QD_t = '1'
                                    else:
                                        QD_t = '0'
                    else:
                        if QA_t == '1':
                            QA_t = '0'
                        else:
                            QA_t = '1'
                            if QB_t == '1':
                                QB_t = '0'
                            else:
                                QB_t = '1'
                                if QC_t == '1':
                                    QC_t = '0'
                                else:
                                    QC_t = '1'
                                    if QD_t == '1':
                                        QD_t = '0'
                                    else:
                                        QD_t = '1'

                QA, QB, QC, QD = QA_t, QB_t, QC_t, QD_t

        if QA_t == '1' and QB_t == '1' and QC_t == '1' and QD_t == '1' and UD == '1' and ENT == '0':
            RCO = '0'
        elif QA_t == '0' and QB_t == '0' and QC_t == '0' and QD_t == '0' and UD == '0' and ENT == '0':
            RCO = '0'
        else:
            RCO = '1'

        line = f"{LOAD}{UD}{ENT}{ENP}{CLK}{A}{B}{C}{D}{QA}{QB}{QC}{QD}{RCO}\n"
        test_file.write(line)

print(f"Данные записанны в файл: {file_path}")
