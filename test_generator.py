import random

def generate_test_cases(num_test_cases, min_size, max_size, min_val, max_val):
   
    test_cases = []
    for _ in range(num_test_cases):
        size = random.randint(min_size, max_size)
        test_case = [random.randint(min_val, max_val) for _ in range(size)]
        test_cases.append(test_case)
    return test_cases


if __name__ == "__main__":

    num_test_cases = 10
    min_size = 5
    max_size = 20
    min_val = 0
    max_val = 100

    test_cases = generate_test_cases(num_test_cases, min_size, max_size, min_val, max_val)
    for i, test_case in enumerate(test_cases):
        print(f"Test Case {i+1}: {test_case}")
