def maximize_string(t, test_cases):
    results = []

    for s in test_cases:
        s = list(s)  # 将字符串转换为列表，便于修改
        n = len(s)

        # 从左到右遍历每个字符
        for i in range(n):
            # 尝试增大当前位，通过检查后面9位数字来找到最合适的操作
            for j in range(i + 1, min(i + 10, n)):
                if int(s[i]) < int(s[j]) - 1:
                    # 增益操作，选择增大 s[i] 和 s[j]
                    s[i] = str(int(s[j]) - 1)
                    s[j] = str(int(s[i]) + 1)

                    # 检查是否需要回退，确保没有错过更优操作
                    k = i
                    while k > 0 and int(s[k - 1]) < int(s[k]) - 1:
                        s[k - 1] = str(int(s[k]) - 1)
                        s[k] = str(int(s[k - 1]) + 1)
                        k -= 1

                    break  # 一旦增益操作完成，继续处理下一个字符

        results.append("".join(s))  # 将结果转回字符串

    return results


# 读取输入
t = int(input())  # 测试用例数量
test_cases = [input().strip() for _ in range(t)]  # 读取测试用例

# 输出结果
results = maximize_string(t, test_cases)
for result in results:
    print(result)
