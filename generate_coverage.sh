lcov --capture --directory build/tests/CMakeFiles/raytracer_tests.dir --output-file build/tests/CMakeFiles/raytracer_tests.dir/raytracer_test_coverage.info
lcov --remove build/tests/CMakeFiles/raytracer_tests.dir/raytracer_test_coverage.info -o build/tests/CMakeFiles/raytracer_tests.dir/raytracer_test_coverage.info \
"/Applications/Xcode.app/*" \
"`pwd`/lib/*" \
"usr/include/*"
genhtml build/tests/CMakeFiles/raytracer_tests.dir/raytracer_test_coverage.info --output-directory test-coverage