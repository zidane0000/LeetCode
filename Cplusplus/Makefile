CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC = src/Source.cpp
OUT = leetcode.exe

.PHONY: all clean grepDiffOld grepDiff


all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)

grepDiffOld:
	@git diff | awk '/^\+\/\/[0-9]+\./ { \
		if (match($$0, /^\+\/\/([0-9]+)\. (.*)$$/, arr)) \
			num = arr[1]; \
			title = arr[2]; \
			if (getline > 0 && $$0 ~ /^\+\/\//) { \
				print "- [" num "]. " title; \
				info = substr($$0, 4); \
				print "  - " info; \
			} \
	}'

grepDiff:
	@git diff | awk ' \
		function print_block() { \
			if (num != "") { \
				printf("- [%s]. %s\n", num, title); \
				for (i=1; i<=info_count; i++) \
					printf("  - %s\n", info[i]); \
			} \
		} \
		/^\+\/\/\s*[0-9]+\./ { \
			print_block(); \
			delete info; info_count = 0; \
			match($$0, /^\+\/\/\s*([0-9]+)\. (.*)$$/, arr); \
			num = arr[1]; \
			title = arr[2]; \
			next; \
		} \
		/^\+\/\// { \
			line = substr($$0, 4); \
			sub(/^ +/, "", line); \
			if (line ~ /^https?:\/\//) { \
				last_url = line; \
			} else if (line ~ /%$$/) { \
				if (last_url != "") { \
					info[++info_count] = line " [Ref](" last_url ")"; \
					last_url = ""; \
				} else { \
					info[++info_count] = line; \
				} \
			} \
			next; \
		} \
		END { \
			print_block(); \
		}'

rebuild: clean all