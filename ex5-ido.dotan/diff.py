import filecmp
import sys
import re

NEED_TO_BE_SAME = {1, 2, 3}

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: python3 diff.py <file1> <file2>")
        exit(1)

    test_path = sys.argv[2]
    student_path = sys.argv[1]
    regex = re.compile(r'\d+')
    test_num = int(regex.findall(test_path)[-1])

    if test_num in NEED_TO_BE_SAME:
        try:
            if filecmp.cmp(sys.argv[1], sys.argv[2], shallow=False):
                exit(0)
            exit(1)
        except FileNotFoundError:
            print("At least one of the given files was not found.")
            exit(1)
    else:

        try:
            with open(student_path, "r") as stu_file:
                stu_content = stu_file.read()
                stu_content = "".join(stu_content.split())

            if stu_content is None:
                exit(1)

            with open(test_path, "r") as test_file:
                test_file = test_file.read()
                test_file = "".join(test_file.split())

            if test_file != stu_content:
                exit(1)
            exit(0)
        except FileNotFoundError:
            print("At least one of the given files was not found.")
            exit(1)
