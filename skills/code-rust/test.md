# Test

This section covers best practices and guidelines for writing tests in Rust, including unit tests, integration tests, property-based tests, and benchmarking.

- [`test-arrange-act-assert`](rules/test-arrange-act-assert.md) - Structure tests with clear Arrange, Act, Assert sections
- [`test-cfg-test-module`](rules/test-cfg-test-module.md) - Put unit tests in `#[cfg(test)] mod tests { }` within each module
- [`test-criterion-bench`](rules/test-criterion-bench.md) - Use `criterion` for benchmarking
- [`test-descriptive-names`](rules/test-descriptive-names.md) - Use descriptive test names that explain what is being tested
- [`test-doctest-examples`](rules/test-doctest-examples.md) - Keep documentation examples as executable doctests
- [`test-fixture-raii`](rules/test-fixture-raii.md) - Use RAII pattern (Drop trait) for automatic test cleanup
- [`test-integration-dir`](rules/test-integration-dir.md) - Put integration tests in the `tests/` directory
- [`test-loom-concurrency`](rules/test-loom-concurrency.md) - Use `loom` to exhaustively test lock-free and concurrent code
- [`test-mock-traits`](rules/test-mock-traits.md) - Use traits for dependencies to enable mocking in tests
- [`test-mockall-mocking`](rules/test-mockall-mocking.md) - Use mockall for trait mocking
- [`test-proptest-properties`](rules/test-proptest-properties.md) - Use proptest for property-based testing
- [`test-should-panic`](rules/test-should-panic.md) - Use `#[should_panic]` to test that code panics as expected
- [`test-snapshot-testing`](rules/test-snapshot-testing.md) - Use snapshot testing (insta) for complex or serialized output
- [`test-tokio-async`](rules/test-tokio-async.md) - Use `#[tokio::test]` for async tests
- [`test-use-super`](rules/test-use-super.md) - Use `use super::*;` in test modules to access parent module items
