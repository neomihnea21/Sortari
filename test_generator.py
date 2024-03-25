import random


def generate_test_cases(num_test_cases, min_size, max_size, min_val, max_val):
    test_cases = []
    for _ in range(num_test_cases):
        size = random.randint(min_size, max_size)
        test_case = [random.randrange(min_val, max_val) for _ in range(size)]
        test_cases.append(test_case)
    return test_cases


if __name__ == "__main__":
    f=open("teste.out", "w")
    num_test_cases = 1
    min_size = 100000
    max_size = 200000
    min_val = 1
    max_val = 10**6
    test_cases = generate_test_cases(num_test_cases, min_size, max_size, min_val, max_val)
    for testcase in test_cases:
        f.write(str(len(testcase))+ '\n')
        f.write(' '.join(str(x) for x in testcase) + '\n')
