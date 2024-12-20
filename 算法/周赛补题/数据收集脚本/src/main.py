
import os
import re
import json
import sys
import time
import argparse
from collections import defaultdict
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler
import matplotlib.pyplot as plt
from matplotlib import font_manager
from threading import Timer  # 导入定时器


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
    """ 设置中文字体 """
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
        plt.rcParams['font.family'] = 'Arial'


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


def scan_directory(directory, mode):
    """ 扫描目录及子目录中的所有文件并提取信息 """
    file_info = []
    for root, dirs, files in os.walk(directory):
        for filename in files:
            if filename.endswith(".md"):
                div_match, types = analyze_filename(filename)
                if div_match:
                    file_info.append((div_match, types))
                # 打印文件扫描日志，无论是在 1 模式还是 0 模式下
                print(f"扫描文件: {filename}")
    return file_info


# ------------------------------ 绘图和输出 ------------------------------
def plot_statistics(div_counts, type_counts, save_path):
    """ 可视化统计信息并保存为 PNG 图片，自动调整图片质量和字体排版 """
    
    # 获取 divs 和 types 的数量
    num_divs = len(div_counts)
    num_types = len(type_counts)
    
    # 计算数据规模：divs 和 types 的乘积
    data_size = num_divs * num_types
    
    # 根据数据规模调整图像大小、DPI 和字体
    if data_size <= 20:
        fig_width = max(10, num_divs * 0.6)
        fig_height = max(6, num_types * 0.4)
        dpi = 120  # 非常小数据使用低 DPI
        font_size = 8
    elif data_size <= 50:
        fig_width = max(12, num_divs * 0.7)
        fig_height = max(7, num_types * 0.5)
        dpi = 150
        font_size = 10
    elif data_size <= 100:
        fig_width = max(14, num_divs * 0.8)
        fig_height = max(8, num_types * 0.6)
        dpi = 175
        font_size = 12
    elif data_size <= 200:
        fig_width = max(16, num_divs * 1.0)
        fig_height = max(10, num_types * 0.7)
        dpi = 200
        font_size = 14
    elif data_size <= 500:
        fig_width = max(18, num_divs * 1.2)
        fig_height = max(12, num_types * 0.8)
        dpi = 225
        font_size = 16
    elif data_size <= 1000:
        fig_width = max(20, num_divs * 1.5)
        fig_height = max(14, num_types * 1.0)
        dpi = 250
        font_size = 18
    else:
        fig_width = max(24, num_divs * 2.0)
        fig_height = max(18, num_types * 1.2)
        dpi = 300
        font_size = 20
    
    # 创建图像并设置大小和分辨率
    plt.figure(figsize=(fig_width, fig_height), dpi=dpi)
    
    # 指定 div 的排序顺序
    div_order = ['div1', 'div2', 'div3', 'div4', 'div5']
    # 按照指定顺序绘制 div 的条形图
    ordered_div_counts = {div: div_counts[div] for div in div_order if div in div_counts}
    
    # div1-div5 分布
    plt.subplot(1, 2, 1)
    plt.bar(ordered_div_counts.keys(), ordered_div_counts.values(), color='lightblue')
    plt.title("div1到div5分布", fontsize=font_size)
    plt.xlabel("div类别", fontsize=font_size)
    plt.ylabel("数量", fontsize=font_size)
    
    # 动态调整字体大小，根据图像尺寸
    xticks_fontsize = max(font_size, fig_width // len(ordered_div_counts))
    plt.xticks(rotation=45, ha='right', fontsize=xticks_fontsize)
    
    # 类型分布
    plt.subplot(1, 2, 2)
    plt.bar(type_counts.keys(), type_counts.values(), color='lightgreen')
    plt.title("类型分布", fontsize=font_size)
    plt.xlabel("类型", fontsize=font_size)
    plt.ylabel("数量", fontsize=font_size)
    
    # 动态调整字体大小
    xticks_fontsize = max(font_size, fig_width // num_types)
    plt.xticks(rotation=45, ha='right', fontsize=xticks_fontsize)
    
    # 优化布局，避免标签重叠
    plt.tight_layout()
    
    # 保存图片
    plt.savefig(save_path)
    print(f"统计图表已保存到：{save_path}")

def print_statistics(file_info, save_directory):
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

    # 确定保存路径
    save_path = os.path.join(save_directory, "训练数据.png")
    os.makedirs(save_directory, exist_ok=True)
    plot_statistics(div_counts, type_counts, save_path)


# ------------------------------ 文件夹监听 ------------------------------
class DirectoryHandler(FileSystemEventHandler):
    """ 文件夹变化事件处理 """

    def __init__(self, directory, save_directory, mode, interval):
        self.directory = directory
        self.save_directory = save_directory
        self.mode = mode
        self.interval = interval
        self.timer = None  # 定时器，用于延迟执行

    def on_any_event(self, event):
        """ 当任何文件发生变化时，重新扫描并更新统计 """
        if event.event_type != 'modified':  # 仅处理文件修改事件
            return

        # 如果变化的文件在输出目录（例如 PNG 文件）中，则忽略
        if event.src_path.endswith(".png"):
            print(f"忽略变化文件: {event.src_path} (PNG 文件)")
            return

        # 如果已有定时任务正在等待，先取消它
        if self.timer is not None:
            self.timer.cancel()

        # 打印文件变化日志
        print(f"检测到变化: {event.src_path}")

        # 设置定时任务：等待一段时间后更新
        self.timer = Timer(self.interval, self.update_statistics)
        self.timer.start()

    def update_statistics(self):
        """ 更新统计并执行操作 """
        print("开始更新统计...")
        file_info = scan_directory(self.directory, self.mode)
        print_statistics(file_info, self.save_directory)


def start_watching(directory, save_directory, interval, mode):
    """ 启动目录监听 """
    event_handler = DirectoryHandler(directory, save_directory, mode, interval)
    observer = Observer()
    observer.schedule(event_handler, directory, recursive=True)
    observer.start()
    print(f"开始监听目录: {directory}，每 {interval} 秒检查一次")

    try:
        while True:
            time.sleep(interval)  # 使用监听间隔时间
    except KeyboardInterrupt:
        observer.stop()
        print("监听停止")
    observer.join()


# ------------------------------ 主程序入口 ------------------------------
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="文件夹统计工具")
    parser.add_argument(
        "-m", "--mode", type=int, choices=[0, 1], default=1,
        help="运行模式：1 为手动扫描模式，0 为实时监听模式（默认: 1）"
    )
    parser.add_argument(
        "-i", "--interval", type=float, default=2.0,
        help="监听间隔时间，仅在 0 模式下有效（单位：秒，默认: 2.0）"
    )
    args = parser.parse_args()

    # 读取 JSON 配置文件
    config = load_config()
    root_directory = config.get("root_directory", "")
    save_directory = config.get("png_save_directory", "")

    if not root_directory:
        root_directory = os.path.dirname(os.path.abspath(__file__))  # 如果为空，使用当前脚本目录作为根目录

    set_chinese_font(config)  # 设置中文字体

    if args.mode == 1:
        print("手动扫描模式")
        file_info = scan_directory(root_directory, args.mode)
        print_statistics(file_info, save_directory)
    else:
        print("实时监听模式")
        start_watching(root_directory, save_directory, args.interval, args.mode)