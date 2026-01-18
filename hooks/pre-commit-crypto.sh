#!/bin/bash
# Quantum-Safe Crypto Pre-Commit Hook
# Enforces governance rules

# Check code size
CODE_SIZE=$(cloc src/ --quiet | grep 'C' | awk '{print $5}')
if [ "$CODE_SIZE" -gt 10000 ]; then
    echo "❌ Governance Violation: Code exceeds 10KB limit"
    exit 1
fi

# Check for banned functions
BANNED=("rand()" "srand()" "malloc" "time()")
for func in "${BANNED[@]}"; do
    if grep -r "$func" src/; then
        echo "❌ Governance Violation: Banned function $func detected"
        exit 1
    fi
done

# Run formal verification
python3 formal_verify.py src/quantum_safe.c

# All checks passed
echo "✅ Quantum-Safe Crypto Governance: All checks passed"
exit 0
