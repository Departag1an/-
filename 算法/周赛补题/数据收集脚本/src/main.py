import os
import re
import json
import sys
import time
import matplotlib.pyplot as plt
from collections import defaultdict
from matplotlib import font_manager


# ------------------------------ 配置文件处理 ------------------------------
def resource_path(relative_path):
    """ 获取资源文件的路径 """
    try:
        base_path = sys._MEIPASS
    except Exception:
        base_path = os.path.dirname(os.path.abspath(__file__))
    return os.path.join(base_path, relative_path)


def load_config():
    """ 读取 JSON 配置文件 """
    json_path = resource_path("..\data\Script.json")

    if not os.path.exists(json_path):
        print(f"错误: 找不到配置文件 {json_path}")
        sys.exit(1)

    with open(json_path, "r", encoding="utf-8") as f:
        config = json.load(f)

    return config


# ------------------------------ 中文字体设置 ------------------------------
def set_chinese_font(config=None):
    """
    设置中文字体
    如果提供了配置，尝试加载配置文件中的字体路径。
    否则，自动在系统字体中查找支持中文的字体。
    """
    font_found = False

    if config and "font_path" in config:
        font_path = config.get("font_path", "")
        if os.path.exists(font_path):
            plt.rcParams['font.family'] = font_manager.FontProperties(fname=font_path).get_name()
            plt.rcParams['axes.unicode_minus'] = False
            font_found = True
            print(f"已加载字体文件：{font_path}")
        else:
            print(f"未找到指定字体文件：{font_path}，继续搜索系统字体")

    if not font_found:
        print("正在查找系统中的中文字体...")

        font_paths = font_manager.findSystemFonts(fontpaths=None, fontext='ttf')
        for font_path in font_paths:
            font_prop = font_manager.FontProperties(fname=font_path)
            font_name = font_prop.get_name()
            if 'SimHei' in font_name or 'Microsoft YaHei' in font_name:
                plt.rcParams['font.family'] = font_name
                plt.rcParams['axes.unicode_minus'] = False
                font_found = True
                print(f"已找到并加载字体：{font_name}")
                break

    if not font_found:
        print("未能加载中文字体，使用默认字体")
        plt.rcParams['font.family'] = 'Arial'  # 如果未找到中文字体，则使用 Arial


# ------------------------------ 文件分析 ------------------------------
# 用于解析文件名的正则表达式
pattern = r"^(?P<difficulty>.*?)_(?P<types>\{.*?\})_(?P<title>.*?)\.md$"


def analyze_filename(filename):
    """ 解析文件名并返回 div 和类型信息 """
    match = re.match(pattern, filename)
    if match:
        types = match.group("types")[1:-1].split(";")  # 去除花括号并分割类型
        div_match = re.findall(r'div[1-5]', filename)
        return div_match, types
    return None, None


def scan_directory(directory):
    """ 扫描目录及子目录中的所有文件并提取信息 """
    file_info = []
    for root, dirs, files in os.walk(directory):
        for filename in files:
            if filename.endswith(".md"):
                div_match, types = analyze_filename(filename)
                if div_match:
                    file_info.append((div_match, types))
    return file_info


# ------------------------------ 绘图和输出 ------------------------------
def plot_statistics(div_counts, type_counts, save_path):
    """ 可视化统计信息并保存为 PNG 图片 """
    plt.figure(figsize=(12, 6))

    # div1-div5 分布
    plt.subplot(1, 2, 1)
    plt.bar(div_counts.keys(), div_counts.values(), color='lightblue')
    plt.title("div1到div5分布")
    plt.xlabel("div类别")
    plt.ylabel("数量")

    # 类型分布
    plt.subplot(1, 2, 2)
    plt.bar(type_counts.keys(), type_counts.values(), color='lightgreen')
    plt.title("类型分布")
    plt.xlabel("类型")
    plt.ylabel("数量")

    plt.tight_layout()
    plt.savefig(save_path)
    print(f"统计图表已保存到：{save_path}")


def print_statistics(file_info):
    """ 打印统计信息并调用可视化输出 """
    div_counts = defaultdict(int)
    type_counts = defaultdict(int)

    # 统计 div1-div5 分布和类型分布
    for div_match, types in file_info:
        for div in div_match:
            div_counts[div] += 1
        for t in types:
            type_counts[t] += 1

    # 输出文本统计
    print("div1到div5分布:")
    for div, count in div_counts.items():
        print(f"{div}: {count} 个")

    print("\n类型分布:")
    for t, count in type_counts.items():
        print(f"{t}: {count} 个")

    # 获取脚本所在目录
    script_dir = os.path.dirname(os.path.abspath(__file__))

    # 读取配置文件
    config = load_config()

    # 从配置文件中获取根目录路径（如果为空则使用脚本所在目录）
    root_directory = config.get("root_directory", "")
    if not root_directory:
        root_directory = script_dir  # 如果为空，使用当前脚本所在目录作为根目录

    print(f"自动使用根目录：{root_directory}")

    # 从配置文件中获取 PNG 保存目录（相对路径）
    png_save_directory = config.get("png_save_directory", "output")

    # 拼接保存路径，确保目标文件夹存在
    save_dir = os.path.join(script_dir, png_save_directory)
    os.makedirs(save_dir, exist_ok=True)

    # 定义保存的 PNG 路径
    save_path = os.path.join(save_dir, "训练数据.png")

    # 调用绘制并保存函数
    plot_statistics(div_counts, type_counts, save_path)


# ------------------------------ 主程序入口 ------------------------------
if __name__ == "__main__":
    # 获取当前脚本的路径，并获取配置的根目录路径（如果为空，则使用脚本所在目录）
    script_dir = os.path.dirname(os.path.abspath(__file__))

    # 读取 JSON 配置文件
    config = load_config()

    root_directory = config.get("root_directory", "")
    if not root_directory:
        root_directory = script_dir  # 如果为空，使用当前脚本所在目录作为根目录

    print(f"自动使用根目录：{root_directory}")

    # 设置中文字体
    set_chinese_font(config)

    # 扫描该目录及子目录中的所有文件
    file_info = scan_directory(root_directory)

    # 判断运行模式和刷新间隔
    if len(sys.argv) < 2:
        print("错误: 缺少模式参数！")
        sys.exit(1)

    mode = int(sys.argv[1])  # 0: 一次性生成图表, 1: 定时刷新
    if mode == 1:
        if len(sys.argv) < 3:
            print("错误: 缺少时间参数！")
            sys.exit(1)

        interval = int(sys.argv[2])  # 定时刷新间隔（秒）
        while True:
            print_statistics(file_info)
            time.sleep(interval)  # 每隔一定时间刷新一次图表
    else:
        print_statistics(file_info)  # 仅生成一次图表
