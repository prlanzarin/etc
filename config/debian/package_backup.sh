### bash script for backing up package lists and installs
### kudos huckle@askubuntu

## pkg-backup

H_DIR='/home/prlanzarin/backup'

dpkg --get-selections > $H_DIR/Package.list
sudo cp -R /etc/apt/sources.list* $H_DIR/
sudo apt-key exportall > $H_DIR/Repo.keys
rsync --progress /home/`whoami` $H_DIR/
