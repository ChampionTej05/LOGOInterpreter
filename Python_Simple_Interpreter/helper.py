import re 

statement = "REPEAT [FD 40 RT 90]"
pattern = "REPEAT|FD|BK|RT|LT|\d+|\[|\]"
tokens = re.findall(pattern, statement, re.IGNORECASE)
print(tokens)

