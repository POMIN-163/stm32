import xml.dom.minidom as minidom
import os

# 递归获取子目录所有配置文件
def listdir(path, list_name):
    for file in os.listdir(path):
        file_path = os.path.join(path, file)
        if os.path.isdir(file_path):
            listdir(file_path, list_name)
        elif os.path.splitext(file_path)[1] == '.uvoptx':
            list_name.append(file_path)

dir = os.path.abspath(os.path.dirname(os.path.abspath(__file__)) + os.path.sep + ".")
print(dir)
# 获取当前路径
xmlArr = []
listdir(dir, xmlArr)
# 遍历配置文件

Stlink = 'STLink\ST-LINKIII-KEIL_SWO.dll'
Daplink = 'BIN\CMSIS_AGDI.dll'
Jlink = 'Segger\JL2CM3.dll'
download = Stlink
# 选择下载器类型

for xml in xmlArr:
    print(xml)
    dom = minidom.parse(xml)
    names = dom.getElementsByTagName('pMon')[0].childNodes[0].nodeValue
    if names != download:
        txt = open(xml, "r").read()
        txt = txt.replace(names, download)
        xml = open(xml, "w")
        xml.write(txt)
# 写入所有配置文件下载器配置

"""
for xml in xmlArr:
    print(xml)
    dom = minidom.parse(xml)
    names = dom.getElementsByTagName('pMon')[0].childNodes[0].nodeValue
    print(names)
"""
exit()
