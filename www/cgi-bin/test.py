print("Content_type: text/html\r\n")
print("\r\n")
print("<html>")
print("<head>")
print("    <title>pytest</title>")
print("</head>")
print("<body>")
print("       <py-script>")
def wallis(n):
    pi = 2
    for i in range(1,n):
        pi *= 4 * i ** 2 / (4 * i ** 2 - 1)
    return pi

pi = wallis(100000)
s = f"π est approximativement {pi:.3f}"
print(s)
print("        </py-script>")
print("</body>")
print("</html>")
