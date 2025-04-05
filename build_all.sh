source "./build_scripts/detect_runner.sh"

for d in */ ; do
	cd "$d"

	if [ -d "src" ] ; then
		cd "./src"

		sh "./build.sh"

		cd "../"
	fi

	cd "../"
done
