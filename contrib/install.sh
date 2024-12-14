cmakeargs=("-DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX}")
cmakeargs+=("-DCMAKE_BUILD_TYPE=Release")
cmakeargs+=("-DPYTHON_EXECUTABLE:FILEPATH=`which python3`")
cmakeargs+=("-DPYBIND11_TEST=OFF")
install ${PYBIND_ORG:-pybind} pybind11 ${PYBIND_BRANCH:-v2.7.1} \
    ${PYBIND_LOCAL:-pybind11-2.7.1} "${cmakeargs[@]}"