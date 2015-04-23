

github使用说明：

//首先在本地创建ssh key
$ ssh-keygen -t rsa -C "your_email@youremail.com"

//后面的your_email@youremail.com改为你的邮箱，之后会要求确认路径和输入密码，我们这使用默认的一路回车就行。成功的话会在~/下生成.ssh文件夹，进去，打开id_rsa.pub，复制里面的key。
//回到github，进入Account Settings，左边选择SSH Keys，Add SSH Key,title随便填，粘贴key。为了验证是否成功，在git bash下输入：



//测试github
$ ssh -T git@github.com

//配置本地GIT
$ git config --global user.name "your name"  
$ git config --global user.email "your_email@youremail.com"  
//获取Git配置信息，执行以下命令
git config --list
//以下命令会为终端配置高亮
git config --global color.status auto
git config --global color.branch auto




//向github推送文件
$  mkdir test  //创建目录
$  cd test     //进入目录
$  git init    //创建./.git
$  vi  README
$  git add README  //向git增加文件或者目录
$  git commit -m 'first commit'  //向local./.git 提交
$  git remote add origin git@github.com:jiangdoudou/test.git  //必须先在github创建“Repositories”!!
//git remote -v  //git remote add xxxx  ->xxxx表示分支名
$  git push -u origin master //向github 推送



//git branch  此处githubused 分支时增加！！！！！
//向github  提交分支



$ git branch xxxx //xxxx表示分支名
$ git checkout xxxx //切换分支到xxxx


$ git branch//直接输入git branch，不加任何后续参数，就表示让git列出所有已存在的分支

$ git push origin githubused   //githubused 为分支名
