function bv_fms_initialize
{
    export DO_FMS="no"
}

function bv_fms_enable
{
    DO_FMS="yes"
}

function bv_fms_disable
{
    DO_FMS="no"
}

function bv_fms_depends_on
{
    local depends_on="mfem zlib"

    if [[ "$DO_CONDUIT" == "yes" ]] ; then
        depends_on="$depends_on conduit"
    fi

    echo $depends_on
}

function bv_fms_info
{
    export FMS_VERSION=${FMS_VERSION:-"100"}
    export FMS_FILE=${FMS_FILE:-"FMS-${FMS_VERSION}.tar.gz"}
    export FMS_BUILD_DIR=${FMS_BUILD_DIR:-"FMS-${FMS_VERSION}"}
# For now... (need to put final FMS sources into VisIt's third-party repo and update checksums)
    export FMS_URL=${FMS_URL:-"http://visit.ilight.com/assets"}
    export FMS_MD5_CHECKSUM="661ffd43a0588bdc38afad496b56675e"
    export FMS_SHA256_CHECKSUM="7c75f0312a3133b505232ca3dc78f0548a1934b68c9066bd79959a02af58da00"
}

function bv_fms_print
{
    printf "%s%s\n" "FMS_FILE=" "${FMS_FILE}"
    printf "%s%s\n" "FMS_VERSION=" "${FMS_VERSION}"
    printf "%s%s\n" "FMS_BUILD_DIR=" "${FMS_BUILD_DIR}"
}

function bv_fms_print_usage
{
    printf "%-20s %s [%s]\n" "--fms" "Build FMS support" "$DO_FMS"
}

function bv_fms_host_profile
{
    if [[ "$DO_FMS" == "yes" ]] ; then
        echo >> $HOSTCONF
        echo "##" >> $HOSTCONF
        echo "## FMS " >> $HOSTCONF
        echo "##" >> $HOSTCONF
        echo \
            "VISIT_OPTION_DEFAULT(VISIT_FMS_DIR \${VISITHOME}/fms/$FMS_VERSION/\${VISITARCH})" \
            >> $HOSTCONF

        CONDUIT_LIBDEP=""
        if [[ "$DO_CONDUIT" == "yes" ]] ; then
            CONDUIT_LIBDEP="\${VISITHOME}/conduit/$CONDUIT_VERSION/\${VISITARCH}/lib conduit \${VISIT_CONDUIT_LIBDEP}"
#            echo \
#                "VISIT_OPTION_DEFAULT(VISIT_FMS_INCDEP CONDUIT_INCLUDE_DIR TYPE STRING)" \
#                    >> $HOSTCONF
        fi

        echo \
            "VISIT_OPTION_DEFAULT(VISIT_FMS_LIBDEP \${VISITHOME}/mfem/$MFEM_VERSION/\${VISITARCH}/lib mfem $CONDUIT_LIBDEP TYPE STRING)" \
                >> $HOSTCONF
    fi
}

function bv_fms_ensure
{
    if [[ "$DO_FMS" == "yes" ]] ; then
        ensure_built_or_ready "fms" $FMS_VERSION $FMS_BUILD_DIR $FMS_FILE $FMS_URL
        if [[ $? != 0 ]] ; then
            ANY_ERRORS="yes"
            DO_FMS="no"
            error "Unable to build FMS.  ${FMS_FILE} not found."
        fi
    fi
}

function bv_fms_dry_run
{
    if [[ "$DO_FMS" == "yes" ]] ; then
        echo "Dry run option not set for FMS."
    fi
}

# *************************************************************************** #
#                            Function 8, build_fms
# *************************************************************************** #
function build_fms
{
    #
    # Prepare build dir
    #
    prepare_build_dir $FMS_BUILD_DIR $FMS_FILE
    untarred_fms=$?
    if [[ $untarred_fms == -1 ]] ; then
        warn "Unable to prepare FMS build directory. Giving Up!"
        return 1
    fi

    cd $FMS_BUILD_DIR || error "Can't cd to FMS source dir."
    mkdir build
    cd build || error "Can't cd to FMS build dir."

    vopts="-DCMAKE_C_COMPILER:STRING=${C_COMPILER}"
    vopts="${vopts} -DCMAKE_C_FLAGS:STRING=\"${C_OPT_FLAGS}\""
    vopts="${vopts} -DCMAKE_INSTALL_PREFIX:PATH=${VISITDIR}/fms/${FMS_VERSION}/${VISITARCH}"
    if test "x${DO_STATIC_BUILD}" = "xyes" ; then
        vopts="${vopts} -DBUILD_SHARED_LIBS:BOOL=OFF"
    else
        vopts="${vopts} -DBUILD_SHARED_LIBS:BOOL=ON"
    fi
    if [[ "$DO_CONDUIT" == "yes" ]] ; then
        vopts="${vopts} -DCONDUIT_DIR=${VISITDIR}/conduit/${CONDUIT_VERSION}/${VISITARCH}"
    fi

    #
    # Call configure
    #
    info "Configuring FMS . . ."
    CMAKE_BIN="${CMAKE_INSTALL}/cmake"
    if test -e bv_run_cmake.sh ; then
        rm -f bv_run_cmake.sh
    fi
    echo "\"${CMAKE_BIN}\"" ${vopts} .. > bv_run_cmake.sh
    cat bv_run_cmake.sh
    issue_command bash bv_run_cmake.sh || error "FMS configuration failed."

    #
    # Build FMS
    #
    info "Building FMS . . . (~2 minutes)"
    $MAKE $MAKE_OPT_FLAGS
    if [[ $? != 0 ]] ; then
        warn "FMS build failed.  Giving up"
        return 1
    fi

    #
    # Install into the VisIt third party location.
    #
    info "Installing FMS"
    $MAKE install

    if [[ "$DO_GROUP" == "yes" ]] ; then
        chmod -R ug+w,a+rX "$VISITDIR/fms"
        chgrp -R ${GROUP} "$VISITDIR/fms"
    fi
    cd "$START_DIR"    
    info "Done with FMS"
    return 0
}


function bv_fms_is_enabled
{
    if [[ $DO_FMS == "yes" ]]; then
        return 1    
    fi
    return 0
}

function bv_fms_is_installed
{
    check_if_installed "fms" $FMS_VERSION
    if [[ $? == 0 ]] ; then
        return 1
    fi
    return 0
}

function bv_fms_build
{
    cd "$START_DIR"
    if [[ "$DO_FMS" == "yes" ]] ; then
        check_if_installed "fms" $FMS_VERSION
        if [[ $? == 0 ]] ; then
            info "Skipping FMS build.  FMS is already installed."
        else
            info "Building FMS (~2 minutes)"
            build_fms
            if [[ $? != 0 ]] ; then
                error "Unable to build or install FMS.  Bailing out."
            fi
            info "Done building FMS"
        fi
    fi
}
