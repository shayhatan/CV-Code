#### PART 1 ####
# final_grade: Calculates the final grade for each student, and writes the output (while eliminating illegal
# rows from the input file) into the file in `output_path`. Returns the average of the grades.
#   input_path: Path to the file that contains the input
#   output_path: Path to the file that will contain the output

id_index = 0
name_index = 1
semester_index = 2
avg_index = 3
num_of_arg = 4
max_avg = 100
min_avg = 50


def split_field(src_path):
    s = []
    src = open(src_path, 'r')
    for line in src:
        s_temp = line.split(',')
        for i, e in enumerate(s_temp):
            s_temp[i] = " ".join(e.split())
        s += s_temp

    src.close()
    return s


def chek_id(s):
    count = 0
    s = s.replace(" ", "")
    for i, e in enumerate(s):
        if count == 0:
            count += 1
            if e == '0':
                return False
    number_of_letters = len(s) - s.count(" ")
    if number_of_letters != 8:
        return False
    return True


def check_name(s):
    temp = s
    temp = temp.replace(" ", "")
    return temp.isalpha()


def check_semester(s):
    for i, e in enumerate(s):
        if e != ' ':
            if int(e) > 0:
                return True
    return False


def check_avg(s):
    x = 0
    for i, e in enumerate(s):
        x = x * 10 + int(e)
    return max_avg >= x > min_avg


def chek_values(data):
    return chek_id(data[id_index]) and check_name(data[name_index]) and check_semester(
        data[semester_index]) and check_avg(data[avg_index])


def write_to_file(data, path):
    wr = open(path, 'w')
    for e in data:
        wr.write(e)
    wr.close()


def end_grade(s1, s2):
    x = int(s1[7]) + int(s1[6]) * 10
    y = int(s2)
    return (x + y) // 2


def dict_to_list(d):
    new_list = []
    for k, v in d.items():
        new_list += [k + ", " + v + ", " + str(end_grade(k, v)) + "\n"]
    new_list.sort()
    return new_list


def get_avg(d):
    x = 0
    for k, v in d.items():
        x += (end_grade(k, v))
    return x // len(d)


def create_dict(s, num_of_arg):
    my_dict = {}
    temp = []
    for i, e in enumerate(s):
        temp += [e]
        if (i + 1) % num_of_arg == 0:
            if chek_values(temp):
                my_dict[temp[id_index]] = temp[avg_index]
            temp = []

    return my_dict


def final_grade(input_path: str, output_path: str) -> int:
    s = split_field(input_path)
    my_dict = create_dict(s, num_of_arg)

    if len(my_dict) == 0:
        return 0

    write_to_file(dict_to_list(my_dict), output_path)
    return get_avg(my_dict)


#### PART 2 ####
# check_strings: Checks if `s1` can be constructed from `s2`'s characters.
#   s1: The string that we want to check if it can be constructed
#   s2: The string that we want to construct s1 from

def check_appear(string, char):
    count = 0
    for i in string:
        if i == char:
            count += 1
    return count


def check_contain(s1, s2):
    for i in s2:
        if check_appear(s2, i) < check_appear(s1, i):
            return False
    return True


def check_strings(s1: str, s2: str) -> bool:
    new_s1 = s1.lower()
    new_s2 = s2.lower()

    return check_contain(new_s1, new_s2)
