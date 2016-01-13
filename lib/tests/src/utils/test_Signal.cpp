#include "catch.hpp"
#include "../../src/utils/Signal.hpp"

class SignalFixture
{

protected:

    int getCalls() const { return calls; }
    void fireSignal() { signal.fire(1); }
    void addCallback() { signal.addCallback(this, &SignalFixture::callback); }

private:

    void callback(int v) { calls = calls + v; }
    int calls = 0;

    Signal<SignalFixture, int> signal {};
};

namespace
{
    SCENARIO_METHOD(SignalFixture, "Signal" "[Signal, addCallback, fire]")
    {
        GIVEN("A Signal") {
            WHEN("Fired") {
                fireSignal();

                THEN("No callback were called") {
                    CHECK(getCalls() == 0);
                }
            }

            WHEN("1 callback added") {
                addCallback();

                THEN("No callback were called") {
                    CHECK(getCalls() == 0);
                }

                WHEN("Fired once") {
                    fireSignal();

                    THEN("1 callback was called") {
                        CHECK(getCalls() == 1);
                    }
                }

                WHEN("Fired twice") {
                    fireSignal();
                    fireSignal();

                    THEN("1 callback was called") {
                        CHECK(getCalls() == 2);
                    }
                }
            }

            WHEN("3 callback added") {
                addCallback();
                addCallback();
                addCallback();

                THEN("No callback were called") {
                    CHECK(getCalls() == 0);
                }

                WHEN("Fired once") {
                    fireSignal();

                    THEN("3 callback was called") {
                        CHECK(getCalls() == 3);
                    }
                }

                WHEN("Fired twice") {
                    fireSignal();
                    fireSignal();

                    THEN("6 callback was called") {
                        CHECK(getCalls() == 6);
                    }
                }
            }
        }
    }
}
