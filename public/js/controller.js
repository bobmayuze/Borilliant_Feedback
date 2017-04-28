// angulat.module("BlankApp")
// var myApp = 
var myApp = angular.module('BlankApp', []);
myApp.controller('My_Controller', ['$scope', '$http', function($scope, $http) {
    $http.get("/read_feedback_all").success((response)=>{
        $scope.feedbackList = response;
    });
}]);
