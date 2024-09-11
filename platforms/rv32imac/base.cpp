extern void experiment();

int main() { experiment(); }

extern "C" {
void *__dso_handle = (void *)&__dso_handle;

int secondary_main() {
    return main();
}
}
