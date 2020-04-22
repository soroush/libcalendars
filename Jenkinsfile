pipeline {
    agent { docker { image 'ubuntu' } }
    stages {
        stage('build') {
            steps {
                sh './configure'
                sh 'make'
            }
        }
        stage('test') {
            steps {
                sh 'make check'
            }
        }
    }
}
