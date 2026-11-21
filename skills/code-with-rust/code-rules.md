# Rust Code Rules

These rules provide guidelines for writing idiomatic and maintainable Rust code. They cover various aspects such as error handling, async programming, API design, and more.

All rules in this skill are divided into specific categories to help developers follow best practices in different areas of Rust programming.

- [API Design](#api-design)
- [Async Rust](#async-rust)
- [Closures](#closures)
- [Collections](#collections)
- [Concurrency](#concurrency)
- [Const](#const)
- [Control Flow](#control-flow)
- [Conversion](#conversion)
- [Error Handling](#error-handling)
- [Documentation](#documentation)
- [Static Analysis](#static-analysis)
- [Macros](#macros)
- [Memory Management](#memory-management)
- [Name Rules](#name-rules)
- [Number Safety](#number-safety)
- [Ownership](#ownership)
- [Pattern Match](#pattern-match)
- [Security](#security)
- [Trait](#trait)
- [Type](#type)
- [Unsafe Rust](#unsafe-rust)



## API Design

- [`api-builder-must-use`](rules/api-builder-must-use.md) - Mark builder methods with `#[must_use]` to prevent silent drops
- [`api-builder-pattern`](rules/api-builder-pattern.md) - Use Builder pattern for complex construction
- [`api-common-traits`](rules/api-common-traits.md) - Implement standard traits (Debug, Clone, PartialEq, etc.) for public types
- [`api-default-impl`](rules/api-default-impl.md) - Implement `Default` for types with sensible default values
- [`api-extension-trait`](rules/api-extension-trait.md) - Use extension traits to add methods to external types
- [`api-from-not-into`](rules/api-from-not-into.md) - Implement `From<T>`, not `Into<U>` - From gives you Into for free
- [`api-impl-asref`](rules/api-impl-asref.md) - Use `AsRef<T>` when you only need to borrow the inner data
- [`api-impl-fromiterator`](rules/api-impl-fromiterator.md) - Implement `FromIterator` and `Extend` for collection types, and `IntoIterator` for all three reference forms
- [`api-impl-into`](rules/api-impl-into.md) - Accept `impl Into<T>` for flexible APIs, implement `From<T>` for conversions
- [`api-must-use`](rules/api-must-use.md) - Mark types and functions with `#[must_use]` when ignoring results is likely a bug
- [`api-newtype-safety`](rules/api-newtype-safety.md) - Use newtypes to prevent mixing semantically different values
- [`api-non-exhaustive`](rules/api-non-exhaustive.md) - Use `#[non_exhaustive]` on public enums and structs for forward compatibility
- [`api-operator-overload`](rules/api-operator-overload.md) - Overload operators only when the semantics are natural and unsurprising
- [`api-parse-dont-validate`](rules/api-parse-dont-validate.md) - Parse into validated types at boundaries
- [`api-sealed-trait`](rules/api-sealed-trait.md) - Use sealed traits to prevent external implementations while allowing use
- [`api-typestate`](rules/api-typestate.md) - Use typestate pattern to encode state machine invariants in the type system



## Async Rust

- [`async-async-fn-bounds`](rules/async-async-fn-bounds.md) - Use `AsyncFn`/`AsyncFnMut`/`AsyncFnOnce` bounds instead of `F: Fn() -> Fut, Fut: Future`
- [`async-broadcast-pubsub`](rules/async-broadcast-pubsub.md) - Use `broadcast` channel for pub/sub where all subscribers receive all messages
- [`async-bounded-channel`](rules/async-bounded-channel.md) - Use bounded channels to apply backpressure and prevent unbounded memory growth
- [`async-cancel-safety`](rules/async-cancel-safety.md) - Ensure futures used in `tokio::select!` branches are cancellation-safe
- [`async-cancellation-token`](rules/async-cancellation-token.md) - Use `CancellationToken` for graceful shutdown and task cancellation
- [`async-clone-before-await`](rules/async-clone-before-await.md) - Clone Arc/Rc data before await points to avoid holding references across suspension
- [`async-fn-in-trait`](rules/async-fn-in-trait.md) - Use native `async fn` in traits (stable 1.75) instead of the `async_trait` macro
- [`async-join-parallel`](rules/async-join-parallel.md) - Use `join!` or `try_join!` for concurrent independent futures
- [`async-joinset-structured`](rules/async-joinset-structured.md) - Use `JoinSet` for managing dynamic collections of spawned tasks
- [`async-mpsc-queue`](rules/async-mpsc-queue.md) - Use `mpsc` channels for async message queues between tasks
- [`async-no-lock-across-await`](rules/async-no-lock-across-await.md) - Never hold `Mutex`/`RwLock` across `.await`
- [`async-no-lock-await`](rules/async-no-lock-await.md) - Never hold `Mutex`/`RwLock` across `.await`
- [`async-oneshot-response`](rules/async-oneshot-response.md) - Use `oneshot` channel for request-response patterns
- [`async-select-racing`](rules/async-select-racing.md) - Use `select!` to race futures and handle the first to complete
- [`async-spawn-blocking`](rules/async-spawn-blocking.md) - Use `spawn_blocking` for CPU-intensive work
- [`async-tokio-fs`](rules/async-tokio-fs.md) - Use `tokio::fs` instead of `std::fs` in async code
- [`async-tokio-runtime`](rules/async-tokio-runtime.md) - Configure Tokio runtime appropriately for your workload
- [`async-try-join`](rules/async-try-join.md) - Use `try_join!` for concurrent fallible operations with early return on error
- [`async-watch-latest`](rules/async-watch-latest.md) - Use `watch` channel for sharing the latest value with multiple observers



## Closure

- [`closure-disjoint-capture`](rules/closure-disjoint-capture.md) - Capture only what you use; lean on edition-2021 disjoint closure captures
- [`closure-fn-trait-bounds`](rules/closure-fn-trait-bounds.md) - Require the least restrictive `Fn` trait a callback needs (`FnOnce` ⊇ `FnMut` ⊇ `Fn`)
- [`closure-impl-fn-return`](rules/closure-impl-fn-return.md) - Return closures as `impl Fn`/`FnMut`/`FnOnce`, not `Box<dyn Fn>`
- [`closure-move-capture`](rules/closure-move-capture.md) - Use `move` for closures that outlive the current scope; clone before `move` to keep the original
- [`closure-static-vs-dyn`](rules/closure-static-vs-dyn.md) - Accept `impl Fn` (generic) for hot callbacks; use `&dyn Fn`/`Box<dyn Fn>` to cut code size or to store them



## Collections

- [`collection-binaryheap`](rules/collection-binaryheap.md) - Use `BinaryHeap` for a priority queue or repeated max-extraction
- [`collection-map-choice`](rules/collection-map-choice.md) - Pick the map by access pattern: `HashMap` (fast, unordered), `BTreeMap` (sorted / range queries), `IndexMap` (insertion order)
- [`collection-seq-choice`](rules/collection-seq-choice.md) - Default to `Vec`; use `VecDeque` for queue/deque behaviour; avoid `LinkedList`
- [`collection-set-membership`](rules/collection-set-membership.md) - Use `HashSet`/`BTreeSet` for membership tests and dedup, not linear `Vec::contains`



## Concurrency

- [`concurrency-rayon-par-iter`](rules/concurrency-rayon-par-iter.md) - Use rayon's `par_iter()` for CPU-bound data parallelism
- [`concurrency-scoped-threads`](rules/concurrency-scoped-threads.md) - Use `std::thread::scope` to borrow stack data across threads
- [`concurrency-atomic-ordering`](rules/concurrency-atomic-ordering.md) - Use the weakest correct memory `Ordering` for every atomic operation
- [`concurrency-thread-local`](rules/concurrency-thread-local.md) - Prefer `thread_local!` with `Cell`/`RefCell` over `static mut`



## Const

- [`const-block`](rules/const-block.md) - Use inline `const { }` blocks for compile-time evaluation and assertions
- [`const-fn`](rules/const-fn.md) - Make functions `const fn` when they can run at compile time
- [`const-generics`](rules/const-generics.md) - Parameterize over values with const generics `<const N: usize>`
- [`const-vs-static`](rules/const-vs-static.md) - Use `const` for an inlined value and `static` for a single addressed instance



## Control Flow

- [`control-iter-over-index`](rules/control-iter-over-index.md) - Prefer iterating over collections directly instead of using index-based loops

### Conversions

- [`convert-tryfrom-fallible`](rules/convert-tryfrom-fallible.md) - Implement `TryFrom` for fallible conversions instead of ad-hoc conversion functions
- [`convert-fromstr-parsing`](rules/convert-fromstr-parsing.md) - Implement `FromStr` to enable `str::parse` for string-to-type conversions
- [`convert-asmut-mutable`](rules/convert-asmut-mutable.md) - Accept `impl AsMut<T>` for flexible mutable borrowed inputs instead of concrete mutable references


## Error Handling

- [`error-anyhow-app`](rules/error-anyhow-app.md) - Use `anyhow` for application error handling. `#std`
- [`error-context-chain`](rules/error-context-chain.md) - Add context with `.context()` or `.with_context()`
- [`error-custom-type`](rules/error-custom-type.md) - Define custom error types for domain-specific failures
- [`error-doc-errors`](rules/error-doc-errors.md) - Document error conditions with `# Errors` section in doc comments
- [`error-from-impl`](rules/error-from-impl.md) - Implement `From<E>` for error conversions to enable `?` operator
- [`error-lowercase-msg`](rules/error-lowercase-msg.md) - Start error messages lowercase, no trailing punctuation
- [`error-no-errors-drop`](rules/error-no-errors-drop.md) - Avoid dropping errors silently; handle or propagate them explicitly
- [`error-no-lazy-expect`](rules/error-no-lazy-expect.md) - Avoid using `lazy` `expect` messages; prefer early error handling with context
- [`error-no-panic-expected`](rules/error-no-panic-expected.md) - Avoid panicking in code paths where errors are expected; prefer `Result` or `Option`
- [`error-no-unwrap`](rules/error-no-unwrap.md) - Avoid using `unwrap`; prefer proper error handling with `Result` or `Option`
- [`error-question-mark`](rules/error-question-mark.md) - Use `?` operator for clean propagation
- [`error-source-chain`](rules/error-source-chain.md) - Preserve error chains with `#[source]` or `source()` method


## Documentation

- [`doc-all-public`](rules/doc-all-public.md) - Document all public items with `///` doc comments
- [`doc-module-inner`](rules/doc-module-inner.md) - Use `//!` for module-level documentation
- [`doc-examples-section`](rules/doc-examples-section.md) - Include `# Examples` with runnable code
- [`doc-errors-section`](rules/doc-errors-section.md) - Include `# Errors` section for fallible functions
- [`doc-panics-section`](rules/doc-panics-section.md) - Include `# Panics` section for functions that can panic
- [`doc-safety-section`](rules/doc-safety-section.md) - Include `# Safety` section for unsafe functions
- [`doc-question-mark`](rules/doc-question-mark.md) - Use `?` in examples, not `.unwrap()`
- [`doc-hidden-setup`](rules/doc-hidden-setup.md) - Use `# ` prefix to hide example setup code
- [`doc-intra-links`](rules/doc-intra-links.md) - Use intra-doc links to reference types and items
- [`doc-link-types`](rules/doc-link-types.md) - Use intra-doc links to connect related types and functions
- [`doc-cargo-metadata`](rules/doc-cargo-metadata.md) - Fill `Cargo.toml` metadata for published crates
- [`doc-crate-readme`](rules/doc-crate-readme.md) - Unify the README and crate root docs with `#![doc = include_str!("../README.md")]`



## Static Analysis

- [`lint-deny-correctness`](rules/lint-deny-correctness.md) - `#![deny(clippy::correctness)]`
- [`lint-warn-suspicious`](rules/lint-warn-suspicious.md) - Enable clippy::suspicious for likely bugs
- [`lint-warn-style`](rules/lint-warn-style.md) - Enable clippy::style for idiomatic code
- [`lint-warn-complexity`](rules/lint-warn-complexity.md) - Enable clippy::complexity for simpler code
- [`lint-warn-perf`](rules/lint-warn-perf.md) - Enable clippy::perf for performance improvements
- [`lint-pedantic-selective`](rules/lint-pedantic-selective.md) - Enable clippy::pedantic selectively
- [`lint-missing-docs`](rules/lint-missing-docs.md) - Warn on missing documentation for public items
- [`lint-unsafe-doc`](rules/lint-unsafe-doc.md) - Require documentation for unsafe blocks
- [`lint-cargo-metadata`](rules/lint-cargo-metadata.md) - Enable clippy::cargo for published crates
- [`lint-rustfmt-check`](rules/lint-rustfmt-check.md) - Run cargo fmt --check in CI
- [`lint-workspace-lints`](rules/lint-workspace-lints.md) - Configure lints at workspace level for consistent enforcement
- [`lint-cfg-check`](rules/lint-cfg-check.md) - Enable `unexpected_cfgs` and declare known cfgs to catch feature-gate typos
- [`lint-clippy-nursery-selected`](rules/lint-clippy-nursery-selected.md) - Enable high-value `clippy::nursery` lints selectively, not the whole group



## Macros

- [`macro-prefer-functions`](rules/macro-prefer-functions.md) - Reach for a macro only when a function or generic cannot express it
- [`macro-rules-hygiene`](rules/macro-rules-hygiene.md) - Rely on `macro_rules!` hygiene and use `$crate` for paths to your crate's items
- [`macro-fragment-specifiers`](rules/macro-fragment-specifiers.md) - Capture with precise fragment specifiers, not raw `:tt`, where you can
- [`macro-export-crate-path`](rules/macro-export-crate-path.md) - Export declarative macros with `#[macro_export]` and a clean import path
- [`macro-private-helpers`](rules/macro-private-helpers.md) - Hide macro-generated helper items behind a `#[doc(hidden)] pub mod __private`
- [`macro-proc-two-crate`](rules/macro-proc-two-crate.md) - Put procedural macros in a dedicated `proc-macro = true` crate and re-export from the facade
- [`macro-proc-syn-quote`](rules/macro-proc-syn-quote.md) - Build procedural macros with `syn`, `quote`, and `proc-macro2`
- [`macro-proc-error-spans`](rules/macro-proc-error-spans.md) - Report proc-macro errors as spanned compile errors, never by panicking



## Memory Management

- [`mem-avoid-format`](rules/mem-avoid-format.md) - Avoid `format!()` when string literals work
- [`mem-box-large-variant`](rules/mem-box-large-variant.md) - Box large enum variants to reduce overall enum size
- [`mem-boxed-slice`](rules/mem-boxed-slice.md) - Use `Box<[T]>` instead of `Vec<T>` for fixed-size heap data
- [`mem-clone-from`](rules/mem-clone-from.md) - Use `clone_from()` to reuse allocations when repeatedly cloning
- [`mem-compact-string`](rules/mem-compact-string.md) - Use compact string types for memory-constrained string storage
- [`mem-drop-order`](rules/mem-drop-order.md) - Know and control drop order: struct fields drop top-to-bottom, locals in reverse
- [`mem-no-collect-intermediate`](rules/mem-no-collect-intermediate.md) - Avoid collecting intermediate results into memory when unnecessary
- [`mem-no-dyn-alloc-trait`](rules/mem-no-dyn-alloc-trait.md) - Avoid dynamic allocation for trait objects when possible
- [`mem-no-excessive-clone`](rules/mem-no-excessive-clone.md) - Avoid excessive cloning of values, prefer borrowing or references when possible
- [`mem-no-format-hot-path`](rules/mem-no-format-hot-path.md) - Avoid using `format!` in performance-critical paths; prefer stack-allocated formatting or pre-allocated buffers
- [`mem-reuse-collections`](rules/mem-reuse-collections.md) - Clear and reuse collections instead of creating new ones in loops
- [`mem-slice-over-vec`](rules/mem-slice-over-vec.md) - Prefer slicing over creating new `Vec` instances when possible
- [`mem-smaller-integers`](rules/mem-smaller-integers.md) - Use appropriately-sized integers to reduce memory footprint
- [`mem-str-over-string`](rules/mem-str-over-string.md) - Prefer `&str` over `String` when possible to avoid unnecessary heap allocation
- [`mem-take-replace`](rules/mem-take-replace.md) - Use `mem::take` / `mem::replace` to move a value out of a `&mut` without cloning
- [`mem-with-capacity`](rules/mem-with-capacity.md) - Use `with_capacity()` when size is known
- [`mem-write-over-format`](rules/mem-write-over-format.md) - Use `write!()` into existing buffers instead of `format!()` allocations
- [`mem-zero-copy`](rules/mem-zero-copy.md) - Use zero-copy patterns with slices and `Bytes`


## Name Rules

- [`name-acronym-word`](rules/name-acronym-word.md) - Treat acronyms as words in identifiers: `HttpServer`, not `HTTPServer`
- [`name-as-free`](rules/name-as-free.md) - `as_` prefix: free reference conversion
- [`name-consts-screaming`](rules/name-consts-screaming.md) - Use `SCREAMING_SNAKE_CASE` for constants and statics
- [`name-crate-no-rs`](rules/name-crate-no-rs.md) - Don't suffix crate names with `-rs` or `-rust`
- [`name-funcs-snake`](rules/name-funcs-snake.md) - Use `snake_case` for functions, methods, variables, and modules
- [`name-into-ownership`](rules/name-into-ownership.md) - Use `into_` prefix for ownership-consuming conversions
- [`name-is-has-bool`](rules/name-is-has-bool.md) - Use `is_`, `has_`, `can_`, `should_` prefixes for boolean-returning methods
- [`name-iter-convention`](rules/name-iter-convention.md) - Use iter/iter_mut/into_iter for iterator methods
- [`name-iter-method`](rules/name-iter-method.md) - Name iterator methods `iter()`, `iter_mut()`, and `into_iter()` consistently
- [`name-iter-type-match`](rules/name-iter-type-match.md) - Name iterator types after their source method
- [`name-no-get-prefix`](rules/name-no-get-prefix.md) - Omit get_ prefix for simple getters
- [`name-to-expensive`](rules/name-to-expensive.md) - Use `to_` prefix for expensive conversions that allocate or compute
- [`name-type-param-single`](rules/name-type-param-single.md) - Use single uppercase letters for type parameters: `T`, `E`, `K`, `V`
- [`name-types-camel`](rules/name-types-camel.md) - Use `UpperCamelCase` for types, traits, and enum names
- [`name-variants-camel`](rules/name-variants-camel.md) - Use `UpperCamelCase` for enum variants



## Number Safety

- [`num-cast-try-from`](rules/num-cast-try-from.md) - Avoid `as` for narrowing casts; use `From` for widening and `TryFrom` for narrowing
- [`num-float-compare`](rules/num-float-compare.md) - Don't compare floats with `==`; use a tolerance, and `total_cmp` for ordering
- [`num-nonzero`](rules/num-nonzero.md) - Use `NonZero*` types to forbid zero and unlock the niche optimization
- [`num-overflow-explicit`](rules/num-overflow-explicit.md) - Handle integer overflow explicitly: `checked_`/`saturating_`/`wrapping_`/`overflowing_`
- [`num-saturating-clamp`](rules/num-saturating-clamp.md) - Bound values with `clamp` and saturating arithmetic



## Ownership

- [`own-borrow-over-clone`](rules/own-borrow-over-clone.md) - Prefer `&T` borrowing over `.clone()`
- [`own-slice-over-vec`](rules/own-slice-over-vec.md) - Accept `&[T]` not `&Vec<T>`, `&str` not `&String`
- [`own-cow-conditional`](rules/own-cow-conditional.md) - Use `Cow<'a, T>` for conditional ownership
- [`own-arc-shared`](rules/own-arc-shared.md) - Use `Arc<T>` for thread-safe shared ownership
- [`own-rc-single-thread`](rules/own-rc-single-thread.md) - Use `Rc<T>` for shared ownership in single-threaded contexts
- [`own-refcell-interior`](rules/own-refcell-interior.md) - Use `RefCell<T>` for interior mutability in single-threaded code
- [`own-mutex-interior`](rules/own-mutex-interior.md) - Use `Mutex<T>` for interior mutability across threads
- [`own-rwlock-readers`](rules/own-rwlock-readers.md) - Use `RwLock<T>` when reads significantly outnumber writes
- [`own-copy-small`](rules/own-copy-small.md) - Implement `Copy` for small, simple types
- [`own-clone-explicit`](rules/own-clone-explicit.md) - Use explicit `Clone` for types where copying has meaningful cost
- [`own-move-large`](rules/own-move-large.md) - Move large types instead of copying; use `Box` if moves are expensive
- [`own-lifetime-elision`](rules/own-lifetime-elision.md) - Rely on lifetime elision rules; add explicit lifetimes only when required


## Pattern Match

- [`pattern-let-else`](rules/pattern-let-else.md) - Use `let ... else` for early-return pattern extraction
- [`pattern-matches-macro`](rules/pattern-matches-macro.md) - Use `matches!()` for boolean pattern tests
- [`pattern-if-let-chains`](rules/pattern-if-let-chains.md) - Use `if let` chains to combine pattern bindings and conditions
- [`pattern-exhaustive-enum`](rules/pattern-exhaustive-enum.md) - Match owned enums exhaustively; avoid catch-all `_` that hides new variants
- [`pattern-at-bindings`](rules/pattern-at-bindings.md) - Use `@` bindings to capture a value while matching it against a pattern



## Security

- [`security-no-sensitive-data`](rules/security-no-sensitive-data.md) - Never log secrets or PII; redact or skip them



## Trait

- [`trait-associated-type-vs-generic`](rules/trait-associated-type-vs-generic.md) - Use an associated type when each impl has exactly one output type; use a generic parameter when a type can implement the trait for many input types
- [`trait-blanket-impl`](rules/trait-blanket-impl.md) - Use a blanket impl `impl<T: Bound> Trait for T` to give behaviour to every type that satisfies a bound
- [`trait-coherence-newtype`](rules/trait-coherence-newtype.md) - Respect the orphan rule; wrap a foreign type in a newtype to implement a foreign trait on it
- [`trait-default-methods`](rules/trait-default-methods.md) - Define a trait in terms of a few required methods plus defaulted ones built on top of them
- [`trait-dyn-vs-generic`](rules/trait-dyn-vs-generic.md) - Choose static dispatch (generics / `impl Trait`) vs dynamic dispatch (`dyn Trait`) deliberately
- [`trait-object-safety`](rules/trait-object-safety.md) - Keep a trait dyn-compatible (object-safe) when you need `dyn Trait`



## Type

- [`type-newtype-ids`](rules/type-newtype-ids.md) - Wrap IDs in newtypes: `UserId(u64)`
- [`type-newtype-validated`](rules/type-newtype-validated.md) - Use newtypes to enforce validation at construction time
- [`type-enum-states`](rules/type-enum-states.md) - Use enums for mutually exclusive states
- [`type-option-nullable`](rules/type-option-nullable.md) - Use `Option<T>` for values that might not exist
- [`type-result-fallible`](rules/type-result-fallible.md) - Use `Result<T, E>` for operations that can fail
- [`type-phantom-marker`](rules/type-phantom-marker.md) - Use `PhantomData` to express type relationships without runtime cost
- [`type-never-diverge`](rules/type-never-diverge.md) - Use `!` (never type) for functions that never return
- [`type-generic-bounds`](rules/type-generic-bounds.md) - Add trait bounds only where needed, prefer where clauses for readability
- [`type-no-stringly`](rules/type-no-stringly.md) - Avoid stringly-typed APIs; use enums, newtypes, or validated types
- [`type-repr-transparent`](rules/type-repr-transparent.md) - Use `#[repr(transparent)]` for newtypes in FFI contexts
- [`type-deref-coercion`](rules/type-deref-coercion.md) - Implement `Deref`/`DerefMut` only for smart-pointer and transparent wrapper types
- [`type-display-vs-debug`](rules/type-display-vs-debug.md) - Use `Display` for user-facing output and `Debug` for diagnostics; never swap them
- [`type-numeric-fmt`](rules/type-numeric-fmt.md) - Implement `LowerHex`, `UpperHex`, `Octal`, and `Binary` for numeric newtypes



## Unsafe Rust

- [`unsafe-safety-comment`](rules/unsafe-safety-comment.md) - Write a `// SAFETY:` comment above every `unsafe` block and a `# Safety` section in every `unsafe fn`.
- [`unsafe-minimize-scope`](rules/unsafe-minimize-scope.md) - Keep `unsafe` blocks as small as possible — mark only the operation that requires unsafety, not the surrounding safe code.
- [`unsafe-miri-ci`](rules/unsafe-miri-ci.md) - Run `cargo miri test` in CI for every crate that contains `unsafe` code.
- [`unsafe-maybeuninit`](rules/unsafe-maybeuninit.md) - Use `MaybeUninit<T>` for uninitialized memory; never use `mem::uninitialized()` or `mem::zeroed()` for types with validity invariants.
- [`unsafe-extern-block`](rules/unsafe-extern-block.md) - In Rust 2024, wrap `extern` blocks in `unsafe extern { }` and annotate each item as `safe` or `unsafe`.
- [`unsafe-send-sync-manual`](rules/unsafe-send-sync-manual.md) - Document the invariants when manually implementing `Send` or `Sync`; prefer letting the compiler derive them automatically.
- [`unsafe-no-mangle-unsafe`](rules/unsafe-no-mangle-unsafe.md) - In Rust 2024, write `#[unsafe(no_mangle)]`, `#[unsafe(export_name = "...")]`, and `#[unsafe(link_section = "...")]` — not the bare attribute forms.
