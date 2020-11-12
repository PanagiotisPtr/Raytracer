./run_tests.sh
lcov --capture --directory build/tests/CMakeFiles/raytracer_tests.dir --output-file build/tests/CMakeFiles/raytracer_tests.dir/raytracer_test_coverage.info
genhtml build/tests/CMakeFiles/raytracer_tests.dir/raytracer_test_coverage.info --output-directory test-coverage