for f in *.c *.h makefile; do
	echo Processing $f
	rev=`date`
	awk -v rev="$rev" '
BEGIN { FS = "$" }
		
{
	if ( NF >= 2 && index( $2, "Revision:" ) > 0 ) {
		print $1 "$Revision:" rev "$" $3
	}
	else {
		print
	}
}
	' $f >/tmp/$f
	
	cp /tmp/$f $f
done

echo done