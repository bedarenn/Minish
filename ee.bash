echo "------------------------------"
valgrind --tool=memcheck --track-origins=yes --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes -s ./minishell "./tst" "*na*"
echo "------------------------------"
valgrind --tool=memcheck --track-origins=yes --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes -s ./minishell "./tst" "*na.c"
echo "------------------------------"
valgrind --tool=memcheck --track-origins=yes --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes -s ./minishell "./tst" "*een.c"
echo "------------------------------"
valgrind --tool=memcheck --track-origins=yes --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes -s ./minishell "./tst" "*en.c"
echo "------------------------------"
valgrind --tool=memcheck --track-origins=yes --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes -s ./minishell "./tst" "*een*"
echo "------------------------------"
valgrind --tool=memcheck --track-origins=yes --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes -s ./minishell "./tst" "*en*"
echo "------------------------------"
valgrind --tool=memcheck --track-origins=yes --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes -s ./minishell "./tst" "*en."
echo "------------------------------"
valgrind --tool=memcheck --track-origins=yes --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes -s ./minishell "./tst" "*een."
echo "------------------------------"